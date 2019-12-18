#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pdu {scalar_t__ pdu_bhs; } ;
struct keys {int /*<<< orphan*/ * keys_values; int /*<<< orphan*/ ** keys_names; } ;
struct iscsi_bhs_login_response {int /*<<< orphan*/  bhslr_tsih; } ;
struct connection {scalar_t__ conn_session_type; int conn_max_recv_data_segment_limit; int conn_max_send_data_segment_limit; int conn_max_burst_limit; int conn_first_burst_limit; int conn_max_send_data_segment_length; scalar_t__ conn_first_burst_length; scalar_t__ conn_max_burst_length; TYPE_3__* conn_portal; TYPE_1__* conn_target; } ;
struct TYPE_6__ {TYPE_2__* p_portal_group; } ;
struct TYPE_5__ {int /*<<< orphan*/  pg_tag; int /*<<< orphan*/  pg_offload; } ;
struct TYPE_4__ {int /*<<< orphan*/ * t_alias; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSLR_STAGE_FULL_FEATURE_PHASE ; 
 int /*<<< orphan*/  BHSLR_STAGE_OPERATIONAL_NEGOTIATION ; 
 scalar_t__ CONN_SESSION_TYPE_NORMAL ; 
 int KEYS_MAX ; 
 void* MAX_DATA_SEGMENT_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  kernel_limits (int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  keys_add (struct keys*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keys_add_int (struct keys*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 int /*<<< orphan*/  keys_load (struct keys*,struct pdu*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  keys_save (struct keys*,struct pdu*) ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 int /*<<< orphan*/  login_negotiate_key (struct pdu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct keys*) ; 
 struct pdu* login_new_response (struct pdu*) ; 
 struct pdu* login_receive (struct connection*,int) ; 
 int /*<<< orphan*/  login_set_csg (struct pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  login_set_nsg (struct pdu*,int /*<<< orphan*/ ) ; 
 int login_target_redirect (struct connection*,struct pdu*) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 

__attribute__((used)) static void
login_negotiate(struct connection *conn, struct pdu *request)
{
	struct pdu *response;
	struct iscsi_bhs_login_response *bhslr2;
	struct keys *request_keys, *response_keys;
	int i;
	bool redirected, skipped_security;

	if (conn->conn_session_type == CONN_SESSION_TYPE_NORMAL) {
		/*
		 * Query the kernel for various size limits.  In case of
		 * offload, it depends on hardware capabilities.
		 */
		assert(conn->conn_target != NULL);
		conn->conn_max_recv_data_segment_limit = (1 << 24) - 1;
		conn->conn_max_send_data_segment_limit = (1 << 24) - 1;
		conn->conn_max_burst_limit = (1 << 24) - 1;
		conn->conn_first_burst_limit = (1 << 24) - 1;
		kernel_limits(conn->conn_portal->p_portal_group->pg_offload,
		    &conn->conn_max_recv_data_segment_limit,
		    &conn->conn_max_send_data_segment_limit,
		    &conn->conn_max_burst_limit,
		    &conn->conn_first_burst_limit);

		/* We expect legal, usable values at this point. */
		assert(conn->conn_max_recv_data_segment_limit >= 512);
		assert(conn->conn_max_recv_data_segment_limit < (1 << 24));
		assert(conn->conn_max_send_data_segment_limit >= 512);
		assert(conn->conn_max_send_data_segment_limit < (1 << 24));
		assert(conn->conn_max_burst_limit >= 512);
		assert(conn->conn_max_burst_limit < (1 << 24));
		assert(conn->conn_first_burst_limit >= 512);
		assert(conn->conn_first_burst_limit < (1 << 24));
		assert(conn->conn_first_burst_limit <=
		    conn->conn_max_burst_limit);

		/*
		 * Limit default send length in case it won't be negotiated.
		 * We can't do it for other limits, since they may affect both
		 * sender and receiver operation, and we must obey defaults.
		 */
		if (conn->conn_max_send_data_segment_limit <
		    conn->conn_max_send_data_segment_length) {
			conn->conn_max_send_data_segment_length =
			    conn->conn_max_send_data_segment_limit;
		}
	} else {
		conn->conn_max_recv_data_segment_limit =
		    MAX_DATA_SEGMENT_LENGTH;
		conn->conn_max_send_data_segment_limit =
		    MAX_DATA_SEGMENT_LENGTH;
	}

	if (request == NULL) {
		log_debugx("beginning operational parameter negotiation; "
		    "waiting for Login PDU");
		request = login_receive(conn, false);
		skipped_security = false;
	} else
		skipped_security = true;

	/*
	 * RFC 3720, 10.13.5.  Status-Class and Status-Detail, says
	 * the redirection SHOULD be accepted by the initiator before
	 * authentication, but MUST be accepted afterwards; that's
	 * why we're doing it here and not earlier.
	 */
	redirected = login_target_redirect(conn, request);
	if (redirected) {
		log_debugx("initiator redirected; exiting");
		exit(0);
	}

	request_keys = keys_new();
	keys_load(request_keys, request);

	response = login_new_response(request);
	bhslr2 = (struct iscsi_bhs_login_response *)response->pdu_bhs;
	bhslr2->bhslr_tsih = htons(0xbadd);
	login_set_csg(response, BHSLR_STAGE_OPERATIONAL_NEGOTIATION);
	login_set_nsg(response, BHSLR_STAGE_FULL_FEATURE_PHASE);
	response_keys = keys_new();

	if (skipped_security &&
	    conn->conn_session_type == CONN_SESSION_TYPE_NORMAL) {
		if (conn->conn_target->t_alias != NULL)
			keys_add(response_keys,
			    "TargetAlias", conn->conn_target->t_alias);
		keys_add_int(response_keys, "TargetPortalGroupTag",
		    conn->conn_portal->p_portal_group->pg_tag);
	}

	for (i = 0; i < KEYS_MAX; i++) {
		if (request_keys->keys_names[i] == NULL)
			break;

		login_negotiate_key(request, request_keys->keys_names[i],
		    request_keys->keys_values[i], skipped_security,
		    response_keys);
	}

	/*
	 * We'd started with usable values at our end.  But a bad initiator
	 * could have presented a large FirstBurstLength and then a smaller
	 * MaxBurstLength (in that order) and because we process the key/value
	 * pairs in the order they are in the request we might have ended up
	 * with illegal values here.
	 */
	if (conn->conn_session_type == CONN_SESSION_TYPE_NORMAL &&
	    conn->conn_first_burst_length > conn->conn_max_burst_length) {
		log_errx(1, "initiator sent FirstBurstLength > MaxBurstLength");
	}

	log_debugx("operational parameter negotiation done; "
	    "transitioning to Full Feature Phase");

	keys_save(response_keys, response);
	pdu_send(response);
	pdu_delete(response);
	keys_delete(response_keys);
	pdu_delete(request);
	keys_delete(request_keys);
}
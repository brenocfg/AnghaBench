#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pdu {scalar_t__ pdu_bhs; } ;
struct keys {int /*<<< orphan*/ * keys_values; int /*<<< orphan*/ ** keys_names; } ;
struct iscsi_session_limits {int /*<<< orphan*/  isl_max_recv_data_segment_length; int /*<<< orphan*/  isl_max_send_data_segment_length; int /*<<< orphan*/  isl_first_burst_length; int /*<<< orphan*/  isl_max_burst_length; } ;
struct iscsi_bhs_login_response {int bhslr_flags; } ;
struct TYPE_2__ {scalar_t__ isc_discovery; scalar_t__ isc_header_digest; scalar_t__ isc_data_digest; int isc_iser; int /*<<< orphan*/  isc_offload; } ;
struct connection {TYPE_1__ conn_conf; struct iscsi_session_limits conn_limits; } ;

/* Variables and functions */
 int BHSLR_FLAGS_TRANSIT ; 
 scalar_t__ BHSLR_STAGE_FULL_FEATURE_PHASE ; 
 int /*<<< orphan*/  BHSLR_STAGE_OPERATIONAL_NEGOTIATION ; 
 int KEYS_MAX ; 
 int /*<<< orphan*/  keys_add (struct keys*,char*,char*) ; 
 int /*<<< orphan*/  keys_add_int (struct keys*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 int /*<<< orphan*/  keys_load (struct keys*,struct pdu*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  keys_save (struct keys*,struct pdu*) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_warnx (char*,...) ; 
 int /*<<< orphan*/  login_negotiate_key (struct connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pdu* login_new_request (struct connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ login_nsg (struct pdu*) ; 
 struct pdu* login_receive (struct connection*) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 

__attribute__((used)) static void
login_negotiate(struct connection *conn)
{
	struct pdu *request, *response;
	struct keys *request_keys, *response_keys;
	struct iscsi_bhs_login_response *bhslr;
	int i, nrequests = 0;
	struct iscsi_session_limits *isl;

	log_debugx("beginning operational parameter negotiation");
	request = login_new_request(conn, BHSLR_STAGE_OPERATIONAL_NEGOTIATION);
	request_keys = keys_new();

	isl = &conn->conn_limits;
	log_debugx("Limits for offload \"%s\" are "
	    "MaxRecvDataSegment=%d, max_send_dsl=%d, "
	    "MaxBurstLength=%d, FirstBurstLength=%d",
	    conn->conn_conf.isc_offload, isl->isl_max_recv_data_segment_length,
	    isl->isl_max_send_data_segment_length, isl->isl_max_burst_length,
	    isl->isl_first_burst_length);

	/*
	 * The following keys are irrelevant for discovery sessions.
	 */
	if (conn->conn_conf.isc_discovery == 0) {
		if (conn->conn_conf.isc_header_digest != 0)
			keys_add(request_keys, "HeaderDigest", "CRC32C");
		else
			keys_add(request_keys, "HeaderDigest", "None");
		if (conn->conn_conf.isc_data_digest != 0)
			keys_add(request_keys, "DataDigest", "CRC32C");
		else
			keys_add(request_keys, "DataDigest", "None");

		keys_add(request_keys, "ImmediateData", "Yes");
		keys_add_int(request_keys, "MaxBurstLength",
		    isl->isl_max_burst_length);
		keys_add_int(request_keys, "FirstBurstLength",
		    isl->isl_first_burst_length);
		keys_add(request_keys, "InitialR2T", "Yes");
		keys_add(request_keys, "MaxOutstandingR2T", "1");
		if (conn->conn_conf.isc_iser == 1) {
			keys_add_int(request_keys, "InitiatorRecvDataSegmentLength",
			    isl->isl_max_recv_data_segment_length);
			keys_add_int(request_keys, "TargetRecvDataSegmentLength",
			    isl->isl_max_send_data_segment_length);
			keys_add(request_keys, "RDMAExtensions", "Yes");
		} else {
			keys_add_int(request_keys, "MaxRecvDataSegmentLength",
			    isl->isl_max_recv_data_segment_length);
		}
	} else {
		keys_add(request_keys, "HeaderDigest", "None");
		keys_add(request_keys, "DataDigest", "None");
		keys_add_int(request_keys, "MaxRecvDataSegmentLength",
		    isl->isl_max_recv_data_segment_length);
	}

	keys_add(request_keys, "DefaultTime2Wait", "0");
	keys_add(request_keys, "DefaultTime2Retain", "0");
	keys_add(request_keys, "ErrorRecoveryLevel", "0");
	keys_save(request_keys, request);
	keys_delete(request_keys);
	request_keys = NULL;
	pdu_send(request);
	pdu_delete(request);
	request = NULL;

	response = login_receive(conn);
	response_keys = keys_new();
	keys_load(response_keys, response);
	for (i = 0; i < KEYS_MAX; i++) {
		if (response_keys->keys_names[i] == NULL)
			break;

		login_negotiate_key(conn,
		    response_keys->keys_names[i], response_keys->keys_values[i]);
	}

	keys_delete(response_keys);
	response_keys = NULL;

	for (;;) {
		bhslr = (struct iscsi_bhs_login_response *)response->pdu_bhs;
		if ((bhslr->bhslr_flags & BHSLR_FLAGS_TRANSIT) != 0)
			break;

		nrequests++;
		if (nrequests > 5) {
			log_warnx("received login response "
			    "without the \"T\" flag too many times; giving up");
			break;
		}

		log_debugx("received login response "
		    "without the \"T\" flag; sending another request");

		pdu_delete(response);

		request = login_new_request(conn,
		    BHSLR_STAGE_OPERATIONAL_NEGOTIATION);
		pdu_send(request);
		pdu_delete(request);

		response = login_receive(conn);
	}

	if (login_nsg(response) != BHSLR_STAGE_FULL_FEATURE_PHASE)
		log_warnx("received final login response with wrong NSG 0x%x",
		    login_nsg(response));
	pdu_delete(response);

	log_debugx("operational parameter negotiation done; "
	    "transitioning to Full Feature phase");
}
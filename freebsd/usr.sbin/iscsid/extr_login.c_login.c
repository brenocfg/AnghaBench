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
struct keys {char const** keys_names; int /*<<< orphan*/ * keys_values; } ;
struct iscsi_bhs_login_response {int bhslr_flags; } ;
struct TYPE_2__ {char* isc_mutual_user; char* isc_user; char* isc_initiator; char* isc_initiator_alias; scalar_t__ isc_discovery; char* isc_target; char* isc_secret; } ;
struct connection {TYPE_1__ conn_conf; } ;

/* Variables and functions */
 int BHSLR_FLAGS_TRANSIT ; 
 scalar_t__ BHSLR_STAGE_OPERATIONAL_NEGOTIATION ; 
 int /*<<< orphan*/  BHSLR_STAGE_SECURITY_NEGOTIATION ; 
 int KEYS_MAX ; 
 int /*<<< orphan*/  fail (struct connection*,char*) ; 
 int /*<<< orphan*/  keys_add (struct keys*,char*,char*) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 char* keys_find (struct keys*,char*) ; 
 int /*<<< orphan*/  keys_load (struct keys*,struct pdu*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  keys_save (struct keys*,struct pdu*) ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_errx (int,char*,...) ; 
 int /*<<< orphan*/  login_chap (struct connection*) ; 
 int /*<<< orphan*/  login_negotiate (struct connection*) ; 
 int /*<<< orphan*/  login_negotiate_key (struct connection*,char const*,int /*<<< orphan*/ ) ; 
 struct pdu* login_new_request (struct connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ login_nsg (struct pdu*) ; 
 struct pdu* login_receive (struct connection*) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
login(struct connection *conn)
{
	struct pdu *request, *response;
	struct keys *request_keys, *response_keys;
	struct iscsi_bhs_login_response *bhslr2;
	const char *auth_method;
	int i;

	log_debugx("beginning Login phase; sending Login PDU");
	request = login_new_request(conn, BHSLR_STAGE_SECURITY_NEGOTIATION);
	request_keys = keys_new();
	if (conn->conn_conf.isc_mutual_user[0] != '\0') {
		keys_add(request_keys, "AuthMethod", "CHAP");
	} else if (conn->conn_conf.isc_user[0] != '\0') {
		/*
		 * Give target a chance to skip authentication if it
		 * doesn't feel like it.
		 *
		 * None is first, CHAP second; this is to work around
		 * what seems to be LIO (Linux target) bug: otherwise,
		 * if target is configured with no authentication,
		 * and we are configured to authenticate, the target
		 * will erroneously respond with AuthMethod=CHAP
		 * instead of AuthMethod=None, and will subsequently
		 * fail the connection.  This usually happens with
		 * Discovery sessions, which default to no authentication.
		 */
		keys_add(request_keys, "AuthMethod", "None,CHAP");
	} else {
		keys_add(request_keys, "AuthMethod", "None");
	}
	keys_add(request_keys, "InitiatorName",
	    conn->conn_conf.isc_initiator);
	if (conn->conn_conf.isc_initiator_alias[0] != '\0') {
		keys_add(request_keys, "InitiatorAlias",
		    conn->conn_conf.isc_initiator_alias);
	}
	if (conn->conn_conf.isc_discovery == 0) {
		keys_add(request_keys, "SessionType", "Normal");
		keys_add(request_keys,
		    "TargetName", conn->conn_conf.isc_target);
	} else {
		keys_add(request_keys, "SessionType", "Discovery");
	}
	keys_save(request_keys, request);
	keys_delete(request_keys);
	pdu_send(request);
	pdu_delete(request);

	response = login_receive(conn);

	response_keys = keys_new();
	keys_load(response_keys, response);

	for (i = 0; i < KEYS_MAX; i++) {
		if (response_keys->keys_names[i] == NULL)
			break;

		/*
		 * Not interested in AuthMethod at this point; we only need
		 * to parse things such as TargetAlias.
		 *
		 * XXX: This is somewhat ugly.  We should have a way to apply
		 *      all the keys to the session and use that by default
		 *      instead of discarding them.
		 */
		if (strcmp(response_keys->keys_names[i], "AuthMethod") == 0)
			continue;

		login_negotiate_key(conn,
		    response_keys->keys_names[i], response_keys->keys_values[i]);
	}

	bhslr2 = (struct iscsi_bhs_login_response *)response->pdu_bhs;
	if ((bhslr2->bhslr_flags & BHSLR_FLAGS_TRANSIT) != 0 &&
	    login_nsg(response) == BHSLR_STAGE_OPERATIONAL_NEGOTIATION) {
		if (conn->conn_conf.isc_mutual_user[0] != '\0') {
			log_errx(1, "target requested transition "
			    "to operational parameter negotiation, "
			    "but we require mutual CHAP");
		}

		log_debugx("target requested transition "
		    "to operational parameter negotiation");
		keys_delete(response_keys);
		pdu_delete(response);
		login_negotiate(conn);
		return;
	}

	auth_method = keys_find(response_keys, "AuthMethod");
	if (auth_method == NULL)
		log_errx(1, "received response without AuthMethod");
	if (strcmp(auth_method, "None") == 0) {
		if (conn->conn_conf.isc_mutual_user[0] != '\0') {
			log_errx(1, "target does not require authantication, "
			    "but we require mutual CHAP");
		}

		log_debugx("target does not require authentication");
		keys_delete(response_keys);
		pdu_delete(response);
		login_negotiate(conn);
		return;
	}

	if (strcmp(auth_method, "CHAP") != 0) {
		fail(conn, "Unsupported AuthMethod");
		log_errx(1, "received response "
		    "with unsupported AuthMethod \"%s\"", auth_method);
	}

	if (conn->conn_conf.isc_user[0] == '\0' ||
	    conn->conn_conf.isc_secret[0] == '\0') {
		fail(conn, "Authentication required");
		log_errx(1, "target requests CHAP authentication, but we don't "
		    "have user and secret");
	}

	keys_delete(response_keys);
	response_keys = NULL;
	pdu_delete(response);
	response = NULL;

	login_chap(conn);
	login_negotiate(conn);
}
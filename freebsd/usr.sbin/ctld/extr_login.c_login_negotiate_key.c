#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pdu {struct connection* pdu_connection; } ;
struct keys {int dummy; } ;
struct connection {scalar_t__ conn_session_type; int conn_immediate_data; int conn_max_send_data_segment_limit; size_t conn_max_send_data_segment_length; size_t conn_max_recv_data_segment_length; size_t conn_max_recv_data_segment_limit; int conn_max_burst_limit; size_t conn_max_burst_length; int conn_first_burst_limit; size_t conn_first_burst_length; void* conn_data_digest; void* conn_header_digest; int /*<<< orphan*/ * conn_initiator_alias; } ;

/* Variables and functions */
 void* CONN_DIGEST_CRC32C ; 
 scalar_t__ CONN_SESSION_TYPE_DISCOVERY ; 
 int /*<<< orphan*/ * checked_strdup (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keys_add (struct keys*,char const*,char const*) ; 
 int /*<<< orphan*/  keys_add_int (struct keys*,char const*,size_t) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 int login_list_prefers (char const*,char*,char*) ; 
 int /*<<< orphan*/  login_send_error (struct pdu*,int,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
login_negotiate_key(struct pdu *request, const char *name,
    const char *value, bool skipped_security, struct keys *response_keys)
{
	int which;
	size_t tmp;
	struct connection *conn;

	conn = request->pdu_connection;

	if (strcmp(name, "InitiatorName") == 0) {
		if (!skipped_security)
			log_errx(1, "initiator resent InitiatorName");
	} else if (strcmp(name, "SessionType") == 0) {
		if (!skipped_security)
			log_errx(1, "initiator resent SessionType");
	} else if (strcmp(name, "TargetName") == 0) {
		if (!skipped_security)
			log_errx(1, "initiator resent TargetName");
	} else if (strcmp(name, "InitiatorAlias") == 0) {
		if (conn->conn_initiator_alias != NULL)
			free(conn->conn_initiator_alias);
		conn->conn_initiator_alias = checked_strdup(value);
	} else if (strcmp(value, "Irrelevant") == 0) {
		/* Ignore. */
	} else if (strcmp(name, "HeaderDigest") == 0) {
		/*
		 * We don't handle digests for discovery sessions.
		 */
		if (conn->conn_session_type == CONN_SESSION_TYPE_DISCOVERY) {
			log_debugx("discovery session; digests disabled");
			keys_add(response_keys, name, "None");
			return;
		}

		which = login_list_prefers(value, "CRC32C", "None");
		switch (which) {
		case 1:
			log_debugx("initiator prefers CRC32C "
			    "for header digest; we'll use it");
			conn->conn_header_digest = CONN_DIGEST_CRC32C;
			keys_add(response_keys, name, "CRC32C");
			break;
		case 2:
			log_debugx("initiator prefers not to do "
			    "header digest; we'll comply");
			keys_add(response_keys, name, "None");
			break;
		default:
			log_warnx("initiator sent unrecognized "
			    "HeaderDigest value \"%s\"; will use None", value);
			keys_add(response_keys, name, "None");
			break;
		}
	} else if (strcmp(name, "DataDigest") == 0) {
		if (conn->conn_session_type == CONN_SESSION_TYPE_DISCOVERY) {
			log_debugx("discovery session; digests disabled");
			keys_add(response_keys, name, "None");
			return;
		}

		which = login_list_prefers(value, "CRC32C", "None");
		switch (which) {
		case 1:
			log_debugx("initiator prefers CRC32C "
			    "for data digest; we'll use it");
			conn->conn_data_digest = CONN_DIGEST_CRC32C;
			keys_add(response_keys, name, "CRC32C");
			break;
		case 2:
			log_debugx("initiator prefers not to do "
			    "data digest; we'll comply");
			keys_add(response_keys, name, "None");
			break;
		default:
			log_warnx("initiator sent unrecognized "
			    "DataDigest value \"%s\"; will use None", value);
			keys_add(response_keys, name, "None");
			break;
		}
	} else if (strcmp(name, "MaxConnections") == 0) {
		keys_add(response_keys, name, "1");
	} else if (strcmp(name, "InitialR2T") == 0) {
		keys_add(response_keys, name, "Yes");
	} else if (strcmp(name, "ImmediateData") == 0) {
		if (conn->conn_session_type == CONN_SESSION_TYPE_DISCOVERY) {
			log_debugx("discovery session; ImmediateData irrelevant");
			keys_add(response_keys, name, "Irrelevant");
		} else {
			if (strcmp(value, "Yes") == 0) {
				conn->conn_immediate_data = true;
				keys_add(response_keys, name, "Yes");
			} else {
				conn->conn_immediate_data = false;
				keys_add(response_keys, name, "No");
			}
		}
	} else if (strcmp(name, "MaxRecvDataSegmentLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0) {
			login_send_error(request, 0x02, 0x00);
			log_errx(1, "received invalid "
			    "MaxRecvDataSegmentLength");
		}

		/*
		 * MaxRecvDataSegmentLength is a direction-specific parameter.
		 * We'll limit our _send_ to what the initiator can handle but
		 * our MaxRecvDataSegmentLength is not influenced by the
		 * initiator in any way.
		 */
		if ((int)tmp > conn->conn_max_send_data_segment_limit) {
			log_debugx("capping MaxRecvDataSegmentLength "
			    "from %zd to %d", tmp,
			    conn->conn_max_send_data_segment_limit);
			tmp = conn->conn_max_send_data_segment_limit;
		}
		conn->conn_max_send_data_segment_length = tmp;
		conn->conn_max_recv_data_segment_length =
		    conn->conn_max_recv_data_segment_limit;
		keys_add_int(response_keys, name,
		    conn->conn_max_recv_data_segment_length);
	} else if (strcmp(name, "MaxBurstLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0) {
			login_send_error(request, 0x02, 0x00);
			log_errx(1, "received invalid MaxBurstLength");
		}
		if ((int)tmp > conn->conn_max_burst_limit) {
			log_debugx("capping MaxBurstLength from %zd to %d",
			    tmp, conn->conn_max_burst_limit);
			tmp = conn->conn_max_burst_limit;
		}
		conn->conn_max_burst_length = tmp;
		keys_add_int(response_keys, name, tmp);
	} else if (strcmp(name, "FirstBurstLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0) {
			login_send_error(request, 0x02, 0x00);
			log_errx(1, "received invalid FirstBurstLength");
		}
		if ((int)tmp > conn->conn_first_burst_limit) {
			log_debugx("capping FirstBurstLength from %zd to %d",
			    tmp, conn->conn_first_burst_limit);
			tmp = conn->conn_first_burst_limit;
		}
		conn->conn_first_burst_length = tmp;
		keys_add_int(response_keys, name, tmp);
	} else if (strcmp(name, "DefaultTime2Wait") == 0) {
		keys_add(response_keys, name, value);
	} else if (strcmp(name, "DefaultTime2Retain") == 0) {
		keys_add(response_keys, name, "0");
	} else if (strcmp(name, "MaxOutstandingR2T") == 0) {
		keys_add(response_keys, name, "1");
	} else if (strcmp(name, "DataPDUInOrder") == 0) {
		keys_add(response_keys, name, "Yes");
	} else if (strcmp(name, "DataSequenceInOrder") == 0) {
		keys_add(response_keys, name, "Yes");
	} else if (strcmp(name, "ErrorRecoveryLevel") == 0) {
		keys_add(response_keys, name, "0");
	} else if (strcmp(name, "OFMarker") == 0) {
		keys_add(response_keys, name, "No");
	} else if (strcmp(name, "IFMarker") == 0) {
		keys_add(response_keys, name, "No");
	} else if (strcmp(name, "iSCSIProtocolLevel") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp > 2)
			tmp = 2;
		keys_add_int(response_keys, name, tmp);
	} else {
		log_debugx("unknown key \"%s\"; responding "
		    "with NotUnderstood", name);
		keys_add(response_keys, name, "NotUnderstood");
	}
}
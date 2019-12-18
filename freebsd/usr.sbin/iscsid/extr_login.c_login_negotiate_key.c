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
struct iscsi_session_limits {int isl_max_send_data_segment_length; int isl_max_recv_data_segment_length; int isl_max_burst_length; int isl_first_burst_length; } ;
struct TYPE_2__ {int isc_iser; } ;
struct connection {int conn_initial_r2t; int conn_immediate_data; int conn_max_send_data_segment_length; int conn_max_recv_data_segment_length; int conn_max_burst_length; int conn_first_burst_length; TYPE_1__ conn_conf; void* conn_data_digest; void* conn_header_digest; int /*<<< orphan*/  conn_target_alias; struct iscsi_session_limits conn_limits; } ;

/* Variables and functions */
 void* CONN_DIGEST_CRC32C ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 int login_list_prefers (char const*,char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
login_negotiate_key(struct connection *conn, const char *name,
    const char *value)
{
	struct iscsi_session_limits *isl;
	int which, tmp;

	isl = &conn->conn_limits;
	if (strcmp(name, "TargetAlias") == 0) {
		strlcpy(conn->conn_target_alias, value,
		    sizeof(conn->conn_target_alias));
	} else if (strcmp(value, "Irrelevant") == 0) {
		/* Ignore. */
	} else if (strcmp(name, "HeaderDigest") == 0) {
		which = login_list_prefers(value, "CRC32C", "None");
		switch (which) {
		case 1:
			log_debugx("target prefers CRC32C "
			    "for header digest; we'll use it");
			conn->conn_header_digest = CONN_DIGEST_CRC32C;
			break;
		case 2:
			log_debugx("target prefers not to do "
			    "header digest; we'll comply");
			break;
		default:
			log_warnx("target sent unrecognized "
			    "HeaderDigest value \"%s\"; will use None", value);
			break;
		}
	} else if (strcmp(name, "DataDigest") == 0) {
		which = login_list_prefers(value, "CRC32C", "None");
		switch (which) {
		case 1:
			log_debugx("target prefers CRC32C "
			    "for data digest; we'll use it");
			conn->conn_data_digest = CONN_DIGEST_CRC32C;
			break;
		case 2:
			log_debugx("target prefers not to do "
			    "data digest; we'll comply");
			break;
		default:
			log_warnx("target sent unrecognized "
			    "DataDigest value \"%s\"; will use None", value);
			break;
		}
	} else if (strcmp(name, "MaxConnections") == 0) {
		/* Ignore. */
	} else if (strcmp(name, "InitialR2T") == 0) {
		if (strcmp(value, "Yes") == 0)
			conn->conn_initial_r2t = true;
		else
			conn->conn_initial_r2t = false;
	} else if (strcmp(name, "ImmediateData") == 0) {
		if (strcmp(value, "Yes") == 0)
			conn->conn_immediate_data = true;
		else
			conn->conn_immediate_data = false;
	} else if (strcmp(name, "MaxRecvDataSegmentLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0)
			log_errx(1, "received invalid "
			    "MaxRecvDataSegmentLength");
		if (tmp > isl->isl_max_send_data_segment_length) {
			log_debugx("capping max_send_data_segment_length "
			    "from %d to %d", tmp,
			    isl->isl_max_send_data_segment_length);
			tmp = isl->isl_max_send_data_segment_length;
		}
		conn->conn_max_send_data_segment_length = tmp;
		/* We received target's limit, that means it accepted our's. */
		conn->conn_max_recv_data_segment_length =
		    isl->isl_max_recv_data_segment_length;
	} else if (strcmp(name, "MaxBurstLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0)
			log_errx(1, "received invalid MaxBurstLength");
		if (tmp > isl->isl_max_burst_length) {
			log_debugx("capping MaxBurstLength "
			    "from %d to %d", tmp, isl->isl_max_burst_length);
			tmp = isl->isl_max_burst_length;
		}
		conn->conn_max_burst_length = tmp;
	} else if (strcmp(name, "FirstBurstLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0)
			log_errx(1, "received invalid FirstBurstLength");
		if (tmp > isl->isl_first_burst_length) {
			log_debugx("capping FirstBurstLength "
			    "from %d to %d", tmp, isl->isl_first_burst_length);
			tmp = isl->isl_first_burst_length;
		}
		conn->conn_first_burst_length = tmp;
	} else if (strcmp(name, "DefaultTime2Wait") == 0) {
		/* Ignore */
	} else if (strcmp(name, "DefaultTime2Retain") == 0) {
		/* Ignore */
	} else if (strcmp(name, "MaxOutstandingR2T") == 0) {
		/* Ignore */
	} else if (strcmp(name, "DataPDUInOrder") == 0) {
		/* Ignore */
	} else if (strcmp(name, "DataSequenceInOrder") == 0) {
		/* Ignore */
	} else if (strcmp(name, "ErrorRecoveryLevel") == 0) {
		/* Ignore */
	} else if (strcmp(name, "OFMarker") == 0) {
		/* Ignore */
	} else if (strcmp(name, "IFMarker") == 0) {
		/* Ignore */
	} else if (strcmp(name, "RDMAExtensions") == 0) {
		if (conn->conn_conf.isc_iser == 1 &&
		    strcmp(value, "Yes") != 0) {
			log_errx(1, "received unsupported RDMAExtensions");
		}
	} else if (strcmp(name, "InitiatorRecvDataSegmentLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0)
			log_errx(1, "received invalid "
			    "InitiatorRecvDataSegmentLength");
		if ((int)tmp > isl->isl_max_recv_data_segment_length) {
			log_debugx("capping InitiatorRecvDataSegmentLength "
			    "from %d to %d", tmp,
			    isl->isl_max_recv_data_segment_length);
			tmp = isl->isl_max_recv_data_segment_length;
		}
		conn->conn_max_recv_data_segment_length = tmp;
	} else if (strcmp(name, "TargetPortalGroupTag") == 0) {
		/* Ignore */
	} else if (strcmp(name, "TargetRecvDataSegmentLength") == 0) {
		tmp = strtoul(value, NULL, 10);
		if (tmp <= 0) {
			log_errx(1,
			    "received invalid TargetRecvDataSegmentLength");
		}
		if (tmp > isl->isl_max_send_data_segment_length) {
			log_debugx("capping TargetRecvDataSegmentLength "
			    "from %d to %d", tmp,
			    isl->isl_max_send_data_segment_length);
			tmp = isl->isl_max_send_data_segment_length;
		}
		conn->conn_max_send_data_segment_length = tmp;
	} else {
		log_debugx("unknown key \"%s\"; ignoring",  name);
	}
}
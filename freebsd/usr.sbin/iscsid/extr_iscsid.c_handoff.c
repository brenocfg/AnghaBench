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
struct iscsi_daemon_handoff {int /*<<< orphan*/  idh_first_burst_length; int /*<<< orphan*/  idh_max_burst_length; int /*<<< orphan*/  idh_max_send_data_segment_length; int /*<<< orphan*/  idh_max_recv_data_segment_length; int /*<<< orphan*/  idh_immediate_data; int /*<<< orphan*/  idh_initial_r2t; int /*<<< orphan*/  idh_data_digest; int /*<<< orphan*/  idh_header_digest; int /*<<< orphan*/  idh_statsn; int /*<<< orphan*/  idh_tsih; int /*<<< orphan*/  idh_target_alias; int /*<<< orphan*/  idh_socket; int /*<<< orphan*/  idh_session_id; } ;
struct connection {int /*<<< orphan*/  conn_iscsi_fd; int /*<<< orphan*/  conn_first_burst_length; int /*<<< orphan*/  conn_max_burst_length; int /*<<< orphan*/  conn_max_send_data_segment_length; int /*<<< orphan*/  conn_max_recv_data_segment_length; int /*<<< orphan*/  conn_immediate_data; int /*<<< orphan*/  conn_initial_r2t; int /*<<< orphan*/  conn_data_digest; int /*<<< orphan*/  conn_header_digest; int /*<<< orphan*/  conn_statsn; int /*<<< orphan*/  conn_tsih; int /*<<< orphan*/  conn_target_alias; int /*<<< orphan*/  conn_socket; int /*<<< orphan*/  conn_session_id; } ;
typedef  int /*<<< orphan*/  idh ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSIDHANDOFF ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iscsi_daemon_handoff*) ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  memset (struct iscsi_daemon_handoff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
handoff(struct connection *conn)
{
	struct iscsi_daemon_handoff idh;
	int error;

	log_debugx("handing off connection to the kernel");

	memset(&idh, 0, sizeof(idh));
	idh.idh_session_id = conn->conn_session_id;
	idh.idh_socket = conn->conn_socket;
	strlcpy(idh.idh_target_alias, conn->conn_target_alias,
	    sizeof(idh.idh_target_alias));
	idh.idh_tsih = conn->conn_tsih;
	idh.idh_statsn = conn->conn_statsn;
	idh.idh_header_digest = conn->conn_header_digest;
	idh.idh_data_digest = conn->conn_data_digest;
	idh.idh_initial_r2t = conn->conn_initial_r2t;
	idh.idh_immediate_data = conn->conn_immediate_data;
	idh.idh_max_recv_data_segment_length =
	    conn->conn_max_recv_data_segment_length;
	idh.idh_max_send_data_segment_length =
	    conn->conn_max_send_data_segment_length;
	idh.idh_max_burst_length = conn->conn_max_burst_length;
	idh.idh_first_burst_length = conn->conn_first_burst_length;

	error = ioctl(conn->conn_iscsi_fd, ISCSIDHANDOFF, &idh);
	if (error != 0)
		log_err(1, "ISCSIDHANDOFF");
}
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
typedef  scalar_t__ u_int ;
struct sftp_conn {scalar_t__ version; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_FXP_LSTAT ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/ * do_stat (struct sftp_conn*,char const*,int) ; 
 int /*<<< orphan*/ * get_decode_stat (struct sftp_conn*,scalar_t__,int) ; 
 int /*<<< orphan*/  logit (char*) ; 
 int /*<<< orphan*/  send_string_request (struct sftp_conn*,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

Attrib *
do_lstat(struct sftp_conn *conn, const char *path, int quiet)
{
	u_int id;

	if (conn->version == 0) {
		if (quiet)
			debug("Server version does not support lstat operation");
		else
			logit("Server version does not support lstat operation");
		return(do_stat(conn, path, quiet));
	}

	id = conn->msg_id++;
	send_string_request(conn, id, SSH2_FXP_LSTAT, path,
	    strlen(path));

	return(get_decode_stat(conn, id, quiet));
}
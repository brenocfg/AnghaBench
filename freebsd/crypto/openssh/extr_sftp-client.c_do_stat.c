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
 int /*<<< orphan*/  SSH2_FXP_STAT ; 
 int /*<<< orphan*/  SSH2_FXP_STAT_VERSION_0 ; 
 int /*<<< orphan*/ * get_decode_stat (struct sftp_conn*,scalar_t__,int) ; 
 int /*<<< orphan*/  send_string_request (struct sftp_conn*,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

Attrib *
do_stat(struct sftp_conn *conn, const char *path, int quiet)
{
	u_int id;

	id = conn->msg_id++;

	send_string_request(conn, id,
	    conn->version == 0 ? SSH2_FXP_STAT_VERSION_0 : SSH2_FXP_STAT,
	    path, strlen(path));

	return(get_decode_stat(conn, id, quiet));
}
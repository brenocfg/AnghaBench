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
typedef  int /*<<< orphan*/  u_char ;
struct sftp_conn {int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_FXP_FSETSTAT ; 
 scalar_t__ SSH2_FX_OK ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fx2txt (scalar_t__) ; 
 scalar_t__ get_status (struct sftp_conn*,scalar_t__) ; 
 int /*<<< orphan*/  send_string_attrs_request (struct sftp_conn*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 

int
do_fsetstat(struct sftp_conn *conn, const u_char *handle, u_int handle_len,
    Attrib *a)
{
	u_int status, id;

	id = conn->msg_id++;
	send_string_attrs_request(conn, id, SSH2_FXP_FSETSTAT, handle,
	    handle_len, a);

	status = get_status(conn, id);
	if (status != SSH2_FX_OK)
		error("Couldn't fsetstat: %s", fx2txt(status));

	return status == SSH2_FX_OK ? 0 : -1;
}
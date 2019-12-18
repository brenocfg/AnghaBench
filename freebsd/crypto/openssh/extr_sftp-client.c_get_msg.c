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
struct sshbuf {int dummy; } ;
struct sftp_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_msg_extended (struct sftp_conn*,struct sshbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_msg(struct sftp_conn *conn, struct sshbuf *m)
{
	get_msg_extended(conn, m, 0);
}
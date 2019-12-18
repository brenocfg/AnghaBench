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
struct uni_msg {int dummy; } ;
struct ccconn {int dummy; } ;
typedef  enum conn_sig { ____Placeholder_conn_sig } conn_sig ;

/* Variables and functions */
 int sig_conn (struct ccconn*,int,int /*<<< orphan*/ ,struct uni_msg*) ; 

int
cc_conn_sig_msg(struct ccconn *conn, enum conn_sig sig, struct uni_msg *msg)
{

	return (sig_conn(conn, sig, (msg != NULL), msg));
}
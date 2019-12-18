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
struct ccconn {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_CONN ; 
 int /*<<< orphan*/  cc_sig_log (int /*<<< orphan*/ ,char*,struct ccconn*) ; 
 int /*<<< orphan*/  sig_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ccconn*) ; 

void
cc_conn_sig_flush(struct ccconn *conn)
{

	cc_sig_log(conn->cc, "flushing signals to conn %p", conn);
	sig_flush(conn->cc, SIG_CONN, conn);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uni_msg {int dummy; } ;
struct ccsig {int dummy; } ;
struct ccconn {TYPE_1__* cc; } ;
typedef  enum conn_sig { ____Placeholder_conn_sig } conn_sig ;
struct TYPE_3__ {int /*<<< orphan*/  sigs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SIG_CONN ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cc_conn_sigtab ; 
 int /*<<< orphan*/  cc_sig_log (TYPE_1__*,char*,int /*<<< orphan*/ ,struct ccconn*) ; 
 int /*<<< orphan*/  link ; 
 struct ccsig* sig_alloc (TYPE_1__*,int /*<<< orphan*/ ,struct ccconn*,int /*<<< orphan*/ ,int,struct uni_msg*,int /*<<< orphan*/ ) ; 

int
cc_conn_sig_msg_nodef(struct ccconn *conn, enum conn_sig sig,
    struct uni_msg *msg)
{
	struct ccsig *s;

	s = sig_alloc(conn->cc, SIG_CONN, conn, (msg != NULL), sig, msg, 0);
	if (s == NULL)
		return (ENOMEM);

	TAILQ_INSERT_TAIL(&conn->cc->sigs, s, link);
	cc_sig_log(conn->cc, "queuing sig %s to conn %p",
	    cc_conn_sigtab[sig], conn);

	return (0);
}
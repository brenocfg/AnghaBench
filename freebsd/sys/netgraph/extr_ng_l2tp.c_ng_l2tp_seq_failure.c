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
struct ng_mesg {int dummy; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_3__ {int /*<<< orphan*/  ftarget; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_L2TP_ACK_FAILURE ; 
 int /*<<< orphan*/  NGM_L2TP_COOKIE ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_ID (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_l2tp_seq_failure(priv_p priv)
{
	struct ng_mesg *msg;
	int error;

	NG_MKMESSAGE(msg, NGM_L2TP_COOKIE, NGM_L2TP_ACK_FAILURE, 0, M_NOWAIT);
	if (msg == NULL)
		return;
	NG_SEND_MSG_ID(error, priv->node, msg, priv->ftarget, 0);
}
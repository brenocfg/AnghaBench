#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ng_mesg {int dummy; } ;
typedef  TYPE_2__* priv_p ;
struct TYPE_4__ {int /*<<< orphan*/ * hook; } ;
struct TYPE_5__ {TYPE_1__ one; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_FLOW_COOKIE ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_HOOK (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_one2many_notify(priv_p priv, uint32_t cmd)
{
	struct ng_mesg *msg;
	int dummy_error = 0;

	if (priv->one.hook == NULL)
		return;

	NG_MKMESSAGE(msg, NGM_FLOW_COOKIE, cmd, 0, M_NOWAIT);
	if (msg != NULL)
		NG_SEND_MSG_HOOK(dummy_error, priv->node, msg, priv->one.hook, 0);
}
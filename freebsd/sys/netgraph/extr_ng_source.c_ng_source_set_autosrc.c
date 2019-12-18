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
typedef  int /*<<< orphan*/  uint32_t ;
struct ng_mesg {scalar_t__ data; } ;
typedef  TYPE_1__* sc_p ;
struct TYPE_3__ {int /*<<< orphan*/  output; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_ETHER_COOKIE ; 
 int /*<<< orphan*/  NGM_ETHER_SET_AUTOSRC ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_HOOK (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_source_set_autosrc(sc_p sc, uint32_t flag)
{
	struct ng_mesg *msg;
	int error = 0;

	NG_MKMESSAGE(msg, NGM_ETHER_COOKIE, NGM_ETHER_SET_AUTOSRC,
	    sizeof (uint32_t), M_NOWAIT);
	if (msg == NULL)
		return(ENOBUFS);

	*(uint32_t *)msg->data = flag;
	NG_SEND_MSG_HOOK(error, sc->node, msg, sc->output, 0);
	return (error);
}
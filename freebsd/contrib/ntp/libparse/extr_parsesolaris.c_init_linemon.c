#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* q_qinfo; struct TYPE_11__* q_next; } ;
typedef  TYPE_3__ queue_t ;
struct TYPE_10__ {char* mi_idname; } ;
struct TYPE_9__ {TYPE_2__* qi_minfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_INSTALL ; 
 TYPE_3__* WR (TYPE_3__*) ; 
 int init_zs_linemon (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  pprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
init_linemon(
	     queue_t *q
	     )
{
	register queue_t *dq;

	dq = WR(q);
	/*
	 * we ARE doing very bad things down here (basically stealing ISR
	 * hooks)
	 *
	 * so we chase down the STREAMS stack searching for the driver
	 * and if this is a known driver we insert our ISR routine for
	 * status changes in to the ExternalStatus handling hook
	 */
	while (dq->q_next)
	{
		dq = dq->q_next;		/* skip down to driver */
	}

	/*
	 * find appropriate driver dependent routine
	 */
	if (dq->q_qinfo && dq->q_qinfo->qi_minfo)
	{
		register char *dname = dq->q_qinfo->qi_minfo->mi_idname;

		pprintf(DD_INSTALL, "init_linemon: driver is \"%s\"\n", dname);

#ifdef sun
		if (dname && !strcmp(dname, "zs"))
		{
			return init_zs_linemon(dq, q);
		}
		else
#endif
		{
			pprintf(DD_INSTALL, "init_linemon: driver \"%s\" not suitable for CD monitoring\n", dname);
			return 0;
		}
	}
	pprintf(DD_INSTALL, "init_linemon: cannot find driver\n");
	return 0;
}
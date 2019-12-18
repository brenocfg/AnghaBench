#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* q_qinfo; } ;
typedef  TYPE_3__ queue_t ;
struct TYPE_9__ {TYPE_1__* qi_minfo; } ;
struct TYPE_8__ {char* mi_idname; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_INSTALL ; 
 int /*<<< orphan*/  close_zs_linemon (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  pprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
close_linemon(
	      queue_t *q,
	      queue_t *my_q
	      )
{
	/*
	 * find appropriate driver dependent routine
	 */
	if (q->q_qinfo && q->q_qinfo->qi_minfo)
	{
		register char *dname = q->q_qinfo->qi_minfo->mi_idname;

#ifdef sun
		if (dname && !strcmp(dname, "zs"))
		{
			close_zs_linemon(q, my_q);
			return;
		}
		pprintf(DD_INSTALL, "close_linemon: cannot find driver close routine for \"%s\"\n", dname);
#endif
	}
	pprintf(DD_INSTALL, "close_linemon: cannot find driver name\n");
}
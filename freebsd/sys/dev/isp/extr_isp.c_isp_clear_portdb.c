#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_5__ {int state; } ;
typedef  TYPE_1__ fcportdb_t ;
struct TYPE_6__ {TYPE_1__* portdb; } ;
typedef  TYPE_2__ fcparam ;

/* Variables and functions */
 TYPE_2__* FCPARAM (int /*<<< orphan*/ *,int) ; 
#define  FC_PORTDB_STATE_CHANGED 133 
#define  FC_PORTDB_STATE_DEAD 132 
#define  FC_PORTDB_STATE_NEW 131 
#define  FC_PORTDB_STATE_NIL 130 
#define  FC_PORTDB_STATE_VALID 129 
#define  FC_PORTDB_STATE_ZOMBIE 128 
 int /*<<< orphan*/  ISPASYNC_DEV_GONE ; 
 int MAX_FC_TARG ; 
 int /*<<< orphan*/  isp_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
isp_clear_portdb(ispsoftc_t *isp, int chan)
{
	fcparam *fcp = FCPARAM(isp, chan);
	fcportdb_t *lp;
	int i;

	for (i = 0; i < MAX_FC_TARG; i++) {
		lp = &fcp->portdb[i];
		switch (lp->state) {
		case FC_PORTDB_STATE_DEAD:
		case FC_PORTDB_STATE_CHANGED:
		case FC_PORTDB_STATE_VALID:
			lp->state = FC_PORTDB_STATE_NIL;
			isp_async(isp, ISPASYNC_DEV_GONE, chan, lp);
			break;
		case FC_PORTDB_STATE_NIL:
		case FC_PORTDB_STATE_NEW:
			lp->state = FC_PORTDB_STATE_NIL;
			break;
		case FC_PORTDB_STATE_ZOMBIE:
			break;
		default:
			panic("Don't know how to clear state %d\n", lp->state);
		}
	}
}
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
struct aoetgt {int dummy; } ;
struct aoedev {int ntargets; struct aoetgt** targets; scalar_t__ maxbcnt; int /*<<< orphan*/  rttdev; int /*<<< orphan*/  rttavg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTTAVG_INIT ; 
 int /*<<< orphan*/  RTTDEV_INIT ; 
 int /*<<< orphan*/  aoecmd_wreset (struct aoetgt*) ; 

void
aoecmd_cleanslate(struct aoedev *d)
{
	struct aoetgt **t, **te;

	d->rttavg = RTTAVG_INIT;
	d->rttdev = RTTDEV_INIT;
	d->maxbcnt = 0;

	t = d->targets;
	te = t + d->ntargets;
	for (; t < te && *t; t++)
		aoecmd_wreset(*t);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nm_ifreq {int /*<<< orphan*/  nifr_name; } ;
struct TYPE_2__ {int (* config ) (struct nm_ifreq*) ;} ;
struct nm_bridge {TYPE_1__ bdg_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDG_RLOCK (struct nm_bridge*) ; 
 int /*<<< orphan*/  BDG_RUNLOCK (struct nm_bridge*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 struct nm_bridge* nm_find_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nm_ifreq*) ; 

int
netmap_bdg_config(struct nm_ifreq *nr)
{
	struct nm_bridge *b;
	int error = EINVAL;

	NMG_LOCK();
	b = nm_find_bridge(nr->nifr_name, 0, NULL);
	if (!b) {
		NMG_UNLOCK();
		return error;
	}
	NMG_UNLOCK();
	/* Don't call config() with NMG_LOCK() held */
	BDG_RLOCK(b);
	if (b->bdg_ops.config != NULL)
		error = b->bdg_ops.config(nr);
	BDG_RUNLOCK(b);
	return error;
}
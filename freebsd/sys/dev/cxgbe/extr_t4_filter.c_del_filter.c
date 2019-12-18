#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ prio; scalar_t__ hash; } ;
struct t4_filter {TYPE_1__ fs; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ftid_tab; int /*<<< orphan*/ * hpftid_tab; int /*<<< orphan*/ * hftid_hash_4t; } ;
struct adapter {int flags; TYPE_2__ tids; } ;

/* Variables and functions */
 int EINVAL ; 
 int FULL_INIT_DONE ; 
 int del_hashfilter (struct adapter*,struct t4_filter*) ; 
 int del_tcamfilter (struct adapter*,struct t4_filter*) ; 
 scalar_t__ separate_hpfilter_region (struct adapter*) ; 

int
del_filter(struct adapter *sc, struct t4_filter *t)
{

	/* No filters possible if not initialized yet. */
	if (!(sc->flags & FULL_INIT_DONE))
		return (EINVAL);

	/*
	 * The checks for tid tables ensure that the locks that del_* will reach
	 * for are initialized.
	 */
	if (t->fs.hash) {
		if (sc->tids.hftid_hash_4t != NULL)
			return (del_hashfilter(sc, t));
	} else if (separate_hpfilter_region(sc) && t->fs.prio) {
		if (sc->tids.hpftid_tab != NULL)
			return (del_tcamfilter(sc, t));
	} else {
		if (sc->tids.ftid_tab != NULL)
			return (del_tcamfilter(sc, t));
	}

	return (EINVAL);
}
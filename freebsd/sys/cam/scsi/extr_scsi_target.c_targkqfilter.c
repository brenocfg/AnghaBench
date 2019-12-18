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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct targ_softc {TYPE_1__ read_select; } ;
struct knote {int /*<<< orphan*/ * kn_fop; scalar_t__ kn_hook; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  targread_filtops ; 

__attribute__((used)) static int
targkqfilter(struct cdev *dev, struct knote *kn)
{
	struct  targ_softc *softc;

	devfs_get_cdevpriv((void **)&softc);
	kn->kn_hook = (caddr_t)softc;
	kn->kn_fop = &targread_filtops;
	knlist_add(&softc->read_select.si_note, kn, 0);
	return (0);
}
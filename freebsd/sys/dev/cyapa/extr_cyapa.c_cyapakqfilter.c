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
struct knote {int kn_filter; void* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct knlist {int dummy; } ;
struct TYPE_2__ {struct knlist si_note; } ;
struct cyapa_softc {TYPE_1__ selinfo; } ;
struct cdev {struct cyapa_softc* si_drv1; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  EVFILT_READ 128 
 int /*<<< orphan*/  cyapa_filtops ; 
 int /*<<< orphan*/  knlist_add (struct knlist*,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cyapakqfilter(struct cdev *dev, struct knote *kn)
{
	struct cyapa_softc *sc;
	struct knlist *knlist;

	sc = dev->si_drv1;

	switch(kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &cyapa_filtops;
		kn->kn_hook = (void *)sc;
		break;
	default:
		return (EOPNOTSUPP);
	}
	knlist = &sc->selinfo.si_note;
	knlist_add(knlist, kn, 0);

	return (0);
}
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
struct knote {int kn_filter; struct beri_softc* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct cdev {struct beri_softc* si_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct beri_softc {TYPE_1__ beri_rsel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  beri_read_filterops ; 
 int /*<<< orphan*/  beri_write_filterops ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_kqfilter(struct cdev *dev, struct knote *kn)
{
	struct beri_softc *sc;

	sc = dev->si_drv1;

	switch(kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &beri_read_filterops;
		break;
	case EVFILT_WRITE:
		kn->kn_fop = &beri_write_filterops;
		break;
	default:
		return(EINVAL);
	}

	kn->kn_hook = sc;
	knlist_add(&sc->beri_rsel.si_note, kn, 0);

	return (0);
}
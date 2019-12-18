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
struct pass_softc {TYPE_1__ read_select; } ;
struct knote {int /*<<< orphan*/ * kn_fop; scalar_t__ kn_hook; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct cam_periph {scalar_t__ softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  passread_filtops ; 

__attribute__((used)) static int
passkqfilter(struct cdev *dev, struct knote *kn)
{
	struct cam_periph *periph;
	struct pass_softc *softc;

	periph = (struct cam_periph *)dev->si_drv1;
	softc = (struct pass_softc *)periph->softc;

	kn->kn_hook = (caddr_t)periph;
	kn->kn_fop = &passread_filtops;
	knlist_add(&softc->read_select.si_note, kn, 0);

	return (0);
}
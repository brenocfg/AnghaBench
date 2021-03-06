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
struct knote {scalar_t__ kn_hook; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
passreadfiltdetach(struct knote *kn)
{
	struct cam_periph *periph;
	struct pass_softc *softc;

	periph = (struct cam_periph *)kn->kn_hook;
	softc = (struct pass_softc *)periph->softc;

	knlist_remove(&softc->read_select.si_note, kn, 0);
}
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
struct ti_pruss_irqsc {TYPE_1__ sc_selinfo; } ;
struct knote {struct ti_pruss_irqsc* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ti_pruss_irq_kqread_detach(struct knote *kn)
{
	struct ti_pruss_irqsc *sc = kn->kn_hook;

	knlist_remove(&sc->sc_selinfo.si_note, kn, 0);
}
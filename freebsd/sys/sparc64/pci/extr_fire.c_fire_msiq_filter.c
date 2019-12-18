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
struct intr_vector {struct fire_msiqarg* iv_icarg; } ;
struct TYPE_2__ {int /*<<< orphan*/  fica_clr; int /*<<< orphan*/  fica_sc; } ;
struct fire_msiqarg {TYPE_1__ fmqa_fica; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTCLR_IDLE ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  fire_msiq_common (struct intr_vector*,struct fire_msiqarg*) ; 

__attribute__((used)) static void
fire_msiq_filter(void *cookie)
{
	struct intr_vector *iv;
	struct fire_msiqarg *fmqa;

	iv = cookie;
	fmqa = iv->iv_icarg;
	/*
	 * For filters we don't use fire_intr_clear() since it would clear
	 * the event queue interrupt while we're still processing the event
	 * queue as filters and associated post-filter handler are executed
	 * directly, which in turn would lead to lost MSIs.  So we clear the
	 * event queue interrupt only once after processing the event queue.
	 * Given that this still guarantees the filters to not be executed
	 * concurrently and no other CPU can clear the event queue interrupt
	 * while the event queue is still processed, we don't even need to
	 * interlock the access to the event queue in this case.
	 */
	critical_enter();
	fire_msiq_common(iv, fmqa);
	FIRE_PCI_WRITE_8(fmqa->fmqa_fica.fica_sc, fmqa->fmqa_fica.fica_clr,
	    INTCLR_IDLE);
	critical_exit();
}
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
struct cam_periph {struct pass_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pass_shutdown_kqueue(void *context, int pending)
{
	struct cam_periph *periph;
	struct pass_softc *softc;

	periph = context;
	softc = periph->softc;

	knlist_clear(&softc->read_select.si_note, /*is_locked*/ 0);
	knlist_destroy(&softc->read_select.si_note);

	/*
	 * Release the reference we held for kqueue.
	 */
	cam_periph_release(periph);
}
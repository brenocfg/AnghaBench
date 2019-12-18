#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct machfb_softc {int /*<<< orphan*/  sc_va; } ;

/* Variables and functions */
 int /*<<< orphan*/  V_DISPLAY_STAND_BY ; 
 int /*<<< orphan*/  machfb_blank_display (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
machfb_shutdown_reset(void *v)
{
	struct machfb_softc *sc = v;

	machfb_blank_display(&sc->sc_va, V_DISPLAY_STAND_BY);
}
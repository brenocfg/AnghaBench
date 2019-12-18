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
struct wsp_softc {int /*<<< orphan*/  sc_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WSP_ENABLED ; 
 int /*<<< orphan*/  WSP_LLEVEL_INFO ; 

__attribute__((used)) static void
wsp_disable(struct wsp_softc *sc)
{
	sc->sc_state &= ~WSP_ENABLED;
	DPRINTFN(WSP_LLEVEL_INFO, "disabled wsp\n");
}
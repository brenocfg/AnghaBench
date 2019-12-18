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
struct atp_softc {int sc_state; } ;

/* Variables and functions */
 int ATP_ENABLED ; 
 int /*<<< orphan*/  ATP_LLEVEL_INFO ; 
 int ATP_VALID ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
atp_disable(struct atp_softc *sc)
{
	sc->sc_state &= ~(ATP_ENABLED | ATP_VALID);
	DPRINTFN(ATP_LLEVEL_INFO, "disabled atp\n");
}
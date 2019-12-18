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
struct atp_softc {int sc_state; int /*<<< orphan*/  sc_status; } ;

/* Variables and functions */
 int ATP_ENABLED ; 
 int /*<<< orphan*/  ATP_LLEVEL_INFO ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atp_init_stroke_pool (struct atp_softc*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
atp_enable(struct atp_softc *sc)
{
	if (sc->sc_state & ATP_ENABLED)
		return (0);

	/* reset status */
	memset(&sc->sc_status, 0, sizeof(sc->sc_status));

	atp_init_stroke_pool(sc);

	sc->sc_state |= ATP_ENABLED;

	DPRINTFN(ATP_LLEVEL_INFO, "enabled atp\n");
	return (0);
}
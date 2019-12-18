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
struct ipw_softc {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IPW_CMD_DISABLE ; 
 int IPW_FLAG_ENABLED ; 
 int ipw_cmd (struct ipw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ipw_waitfordisable (struct ipw_softc*,int) ; 

__attribute__((used)) static int
ipw_disable(struct ipw_softc *sc)
{
	int error;

	if (sc->flags & IPW_FLAG_ENABLED) {
		DPRINTF(("Disable adapter\n"));
		error = ipw_cmd(sc, IPW_CMD_DISABLE, NULL, 0);
		if (error != 0)
			return error;
		error = ipw_waitfordisable(sc, 1);
		if (error != 0)
			return error;
		sc->flags &= ~IPW_FLAG_ENABLED;
	}
	return 0;
}
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
typedef  int /*<<< orphan*/  uint32_t ;
struct rstmgr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_SWWARMRSTREQ ; 
 int /*<<< orphan*/  WRITE4 (struct rstmgr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rstmgr_softc* rstmgr_sc ; 

int
rstmgr_warmreset(uint32_t reg)
{
	struct rstmgr_softc *sc;

	sc = rstmgr_sc;
	if (sc == NULL)
		return (1);

	/* Request warm reset */
	WRITE4(sc, reg, CTRL_SWWARMRSTREQ);

	return (0);
}
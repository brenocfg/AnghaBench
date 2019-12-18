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
struct ichwd_softc {int tco_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO_RLD ; 
 int /*<<< orphan*/  ichwd_write_tco_1 (struct ichwd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ichwd_write_tco_2 (struct ichwd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
ichwd_tmr_reload(struct ichwd_softc *sc)
{
	if (sc->tco_version == 1)
		ichwd_write_tco_1(sc, TCO_RLD, 1);
	else
		ichwd_write_tco_2(sc, TCO_RLD, 1);
}
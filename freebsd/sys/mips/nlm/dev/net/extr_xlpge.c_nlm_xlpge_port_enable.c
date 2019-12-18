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
struct nlm_xlpge_softc {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/  block; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 scalar_t__ SGMIIC ; 
 scalar_t__ XAUIC ; 
 int /*<<< orphan*/  nlm_mac_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_mii_pollstat (void*) ; 

__attribute__((used)) static void
nlm_xlpge_port_enable(struct nlm_xlpge_softc *sc)
{
	if ((sc->type != SGMIIC) && (sc->type != XAUIC))
		return;
	nlm_mac_enable(sc->base_addr, sc->block, sc->type, sc->port);
	nlm_mii_pollstat((void *)sc);
}
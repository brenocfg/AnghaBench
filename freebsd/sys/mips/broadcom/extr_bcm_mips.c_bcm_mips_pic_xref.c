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
struct bcm_mips_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 uintptr_t BHND_BUS_GET_INTR_DOMAIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t
bcm_mips_pic_xref(struct bcm_mips_softc *sc)
{
	uintptr_t xref;

	/* Determine our interrupt domain */
	xref = BHND_BUS_GET_INTR_DOMAIN(device_get_parent(sc->dev), sc->dev,
	    true);
	KASSERT(xref != 0, ("missing interrupt domain"));

	return (xref);
}
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
typedef  scalar_t__ uint8_t ;
struct nct_softc {int /*<<< orphan*/ * iores; } ;
typedef  scalar_t__ reg_t ;

/* Variables and functions */
 scalar_t__ NCT_IO_IOR ; 
 scalar_t__ NCT_LD7_GPIO0_IOR ; 
 scalar_t__ NCT_LD7_GPIO1_IOR ; 

__attribute__((used)) static uint8_t
nct_get_ioreg(struct nct_softc *sc, reg_t reg, int group)
{
	uint8_t ioreg;

	if (sc->iores != NULL)
		ioreg = NCT_IO_IOR + reg;
	else if (group == 0)
		ioreg = NCT_LD7_GPIO0_IOR + reg;
	else
		ioreg = NCT_LD7_GPIO1_IOR + reg;
	return (ioreg);
}
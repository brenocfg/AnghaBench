#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ioh0; int /*<<< orphan*/ * port0; } ;
typedef  int /*<<< orphan*/ * KBDC ;

/* Variables and functions */
 int MAXKBDC ; 
 TYPE_1__** atkbdc_softc ; 

KBDC 
atkbdc_open(int unit)
{
    if (unit <= 0)
	unit = 0;
    if (unit >= MAXKBDC)
	return NULL;
    if ((atkbdc_softc[unit]->port0 != NULL)
	|| (atkbdc_softc[unit]->ioh0 != 0))		/* XXX */
	return (KBDC)atkbdc_softc[unit];
    return NULL;
}
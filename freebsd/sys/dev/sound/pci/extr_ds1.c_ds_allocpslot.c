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
struct sc_info {int pslotfree; struct pbank volatile** pbank; } ;
struct pbank {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static volatile struct pbank *
ds_allocpslot(struct sc_info *sc)
{
	int slot;

	if (sc->pslotfree > 63)
		return NULL;
	slot = sc->pslotfree++;
	return sc->pbank[slot * 2];
}
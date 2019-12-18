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
struct mem_range_softc {int mr_ndesc; int /*<<< orphan*/  mr_desc; scalar_t__ mr_cap; } ;
struct mem_range_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MEMDESC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ppc_mrinit(struct mem_range_softc *sc)
{
	sc->mr_cap = 0;
	sc->mr_ndesc = 8; /* XXX: Should be dynamically expandable */
	sc->mr_desc = malloc(sc->mr_ndesc * sizeof(struct mem_range_desc),
	    M_MEMDESC, M_WAITOK | M_ZERO);
}
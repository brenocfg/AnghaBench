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
struct g_raid3_softc {TYPE_1__* sc_zones; } ;
typedef  enum g_raid3_zones { ____Placeholder_g_raid3_zones } g_raid3_zones ;
struct TYPE_2__ {int /*<<< orphan*/  sz_failed; int /*<<< orphan*/  sz_requested; int /*<<< orphan*/  sz_zone; } ;

/* Variables and functions */
 int G_RAID3_NUM_ZONES ; 
 int /*<<< orphan*/  M_RAID3 ; 
 scalar_t__ g_raid3_use_malloc ; 
 int g_raid3_zone (size_t) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 void* uma_zalloc_arg (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static void *
g_raid3_alloc(struct g_raid3_softc *sc, size_t size, int flags)
{
	void *ptr;
	enum g_raid3_zones zone;

	if (g_raid3_use_malloc ||
	    (zone = g_raid3_zone(size)) == G_RAID3_NUM_ZONES)
		ptr = malloc(size, M_RAID3, flags);
	else {
		ptr = uma_zalloc_arg(sc->sc_zones[zone].sz_zone,
		   &sc->sc_zones[zone], flags);
		sc->sc_zones[zone].sz_requested++;
		if (ptr == NULL)
			sc->sc_zones[zone].sz_failed++;
	}
	return (ptr);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  size_t u_int ;
struct lbc_softc {TYPE_2__* sc_range; TYPE_1__* sc_banks; } ;
struct TYPE_4__ {int addr; int size; int kva; } ;
struct TYPE_3__ {int size; int addr; int kva; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t LBC_DEV_MAX ; 
 int /*<<< orphan*/  OCP85XX_TGTIF_LBC ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int law_enable (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pmap_mapdev (int,int) ; 

__attribute__((used)) static int
lbc_banks_map(struct lbc_softc *sc)
{
	vm_paddr_t end, start;
	vm_size_t size;
	u_int i, r, ranges, s;
	int error;

	bzero(sc->sc_range, sizeof(sc->sc_range));

	/*
	 * Determine number of discontiguous address ranges to program.
	 */
	ranges = 0;
	for (i = 0; i < LBC_DEV_MAX; i++) {
		size = sc->sc_banks[i].size;
		if (size == 0)
			continue;

		start = sc->sc_banks[i].addr;
		for (r = 0; r < ranges; r++) {
			/* Avoid wrap-around bugs. */
			end = sc->sc_range[r].addr - 1 + sc->sc_range[r].size;
			if (start > 0 && end == start - 1) {
				sc->sc_range[r].size += size;
				break;
			}
			/* Avoid wrap-around bugs. */
			end = start - 1 + size;
			if (sc->sc_range[r].addr > 0 &&
			    end == sc->sc_range[r].addr - 1) {
				sc->sc_range[r].addr = start;
				sc->sc_range[r].size += size;
				break;
			}
		}
		if (r == ranges) {
			/* New range; add using insertion sort */
			r = 0;
			while (r < ranges && sc->sc_range[r].addr < start)
				r++;
			for (s = ranges; s > r; s--)
				sc->sc_range[s] = sc->sc_range[s-1];
			sc->sc_range[r].addr = start;
			sc->sc_range[r].size = size;
			ranges++;
		}
	}

	/*
	 * Ranges are sorted so quickly go over the list to merge ranges
	 * that grew toward each other while building the ranges.
	 */
	r = 0;
	while (r < ranges - 1) {
		end = sc->sc_range[r].addr + sc->sc_range[r].size;
		if (end != sc->sc_range[r+1].addr) {
			r++;
			continue;
		}
		sc->sc_range[r].size += sc->sc_range[r+1].size;
		for (s = r + 1; s < ranges - 1; s++)
			sc->sc_range[s] = sc->sc_range[s+1];
		bzero(&sc->sc_range[s], sizeof(sc->sc_range[s]));
		ranges--;
	}

	/*
	 * Configure LAW for the LBC ranges and map the physical memory
	 * range into KVA.
	 */
	for (r = 0; r < ranges; r++) {
		start = sc->sc_range[r].addr;
		size = sc->sc_range[r].size;
		error = law_enable(OCP85XX_TGTIF_LBC, start, size);
		if (error)
			return (error);
		sc->sc_range[r].kva = (vm_offset_t)pmap_mapdev(start, size);
	}

	/* XXX: need something better here? */
	if (ranges == 0)
		return (EINVAL);

	/* Assign KVA to banks based on the enclosing range. */
	for (i = 0; i < LBC_DEV_MAX; i++) {
		size = sc->sc_banks[i].size;
		if (size == 0)
			continue;

		start = sc->sc_banks[i].addr;
		for (r = 0; r < ranges; r++) {
			end = sc->sc_range[r].addr - 1 + sc->sc_range[r].size;
			if (start >= sc->sc_range[r].addr &&
			    start - 1 + size <= end)
				break;
		}
		if (r < ranges) {
			sc->sc_banks[i].kva = sc->sc_range[r].kva +
			    (start - sc->sc_range[r].addr);
		}
	}

	return (0);
}
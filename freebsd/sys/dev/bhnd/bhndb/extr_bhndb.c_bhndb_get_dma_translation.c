#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_4__ {int chip_caps; } ;
struct bhndb_softc {TYPE_3__* bus_res; TYPE_1__ chipid; } ;
struct bhndb_hwcfg {struct bhnd_dma_translation* dma_translations; } ;
struct bhnd_dma_translation {int base_addr; int flags; int addr_mask; int addrext_mask; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
typedef  int bhnd_addr_t ;
struct TYPE_6__ {TYPE_2__* res; struct bhndb_hwcfg* cfg; } ;
struct TYPE_5__ {size_t num_dma_tags; int /*<<< orphan*/ ** dma_tags; } ;

/* Variables and functions */
 int BHND_CAP_BP64 ; 
 scalar_t__ BHND_DMA_ADDR_32BIT ; 
 int BHND_DMA_ADDR_BITMASK (scalar_t__) ; 
 int ENODEV ; 
 int ENOENT ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bhndb_get_dma_translation(device_t dev, device_t child, u_int width,
    uint32_t flags, bus_dma_tag_t *dmat,
    struct bhnd_dma_translation *translation)
{
	struct bhndb_softc			*sc;
	const struct bhndb_hwcfg		*hwcfg;
	const struct bhnd_dma_translation	*match;
	bus_dma_tag_t				 match_dmat;
	bhnd_addr_t				 addr_mask, match_addr_mask;

	sc = device_get_softc(dev);
	hwcfg = sc->bus_res->cfg;

	/* Is DMA supported? */
	if (sc->bus_res->res->dma_tags == NULL)
		return (ENODEV);

	/* Is the requested width supported? */
	if (width > BHND_DMA_ADDR_32BIT) {
		/* Backplane must support 64-bit addressing */
		if (!(sc->chipid.chip_caps & BHND_CAP_BP64))
			width = BHND_DMA_ADDR_32BIT;
	}

	/* Find the best matching descriptor for the requested width */
	addr_mask = BHND_DMA_ADDR_BITMASK(width);

	match = NULL;
	match_addr_mask = 0x0;
	match_dmat = NULL;

	for (size_t i = 0; i < sc->bus_res->res->num_dma_tags; i++) {
		const struct bhnd_dma_translation	*dwin;
		bhnd_addr_t				 masked;

		dwin = &hwcfg->dma_translations[i];

		/* The base address must be device addressable */
		if ((dwin->base_addr & addr_mask) != dwin->base_addr)
			continue;

		/* The flags must match */
		if ((dwin->flags & flags) != flags)
			continue;

		/* The window must cover at least part of our addressable
		 * range */
		masked = (dwin->addr_mask | dwin->addrext_mask) & addr_mask;
		if (masked == 0)
			continue;
	
		/* Is this a better match? */
		if (match == NULL || masked > match_addr_mask) {
			match = dwin;
			match_addr_mask = masked;
			match_dmat = sc->bus_res->res->dma_tags[i];
		}
	}

	if (match == NULL || match_addr_mask == 0)
		return (ENOENT);

	if (dmat != NULL)
		*dmat = match_dmat;

	if (translation != NULL)
		*translation = *match;

	return (0);
}
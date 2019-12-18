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
typedef  int /*<<< orphan*/  uintmax_t ;
struct bhnd_dma_translation {int addr_mask; int addrext_mask; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
typedef  int bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bhndb_dma_tag_create(device_t dev, bus_dma_tag_t parent_dmat,
    const struct bhnd_dma_translation *translation, bus_dma_tag_t *dmat)
{
	bus_dma_tag_t	translation_tag;
	bhnd_addr_t	dt_mask;
	bus_addr_t	lowaddr, highaddr;
	bus_size_t	maxsegsz;
	int		error;

	highaddr = BUS_SPACE_MAXADDR;
	maxsegsz = BUS_SPACE_MAXSIZE;

	/* Determine full addressable mask */
	dt_mask = (translation->addr_mask | translation->addrext_mask);
	KASSERT(dt_mask != 0, ("DMA addr_mask invalid: %#jx",
		(uintmax_t)dt_mask));

	/* (addr_mask|addrext_mask) is our maximum supported address */
	lowaddr = MIN(dt_mask, BUS_SPACE_MAXADDR);

	/* Constrain to translation window size */
	if (translation->addr_mask < maxsegsz)
		maxsegsz = translation->addr_mask;

	/* Create our DMA tag */
	error = bus_dma_tag_create(parent_dmat,
	    1, 0,			/* alignment, boundary */
	    lowaddr, highaddr,
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE, 0,	/* maxsize, nsegments */
	    maxsegsz, 0,		/* maxsegsize, flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &translation_tag);
	if (error) {
		device_printf(dev, "failed to create bridge DMA tag: %d\n",
		    error);
		return (error);
	}

	*dmat = translation_tag;
	return (0);
}
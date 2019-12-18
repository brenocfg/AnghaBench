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
struct sdma_softc {struct sdma_channel* channel; } ;
struct sdma_channel {int in_use; void* bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SDMA_N_CHANNELS ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ kmem_alloc_contig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdma_softc* sdma_sc ; 

int
sdma_alloc(void)
{
	struct sdma_channel *channel;
	struct sdma_softc *sc;
	int found;
	int chn;
	int i;

	sc = sdma_sc;
	found = 0;

	/* Channel 0 can't be used */
	for (i = 1; i < SDMA_N_CHANNELS; i++) {
		channel = &sc->channel[i];
		if (channel->in_use == 0) {
			channel->in_use = 1;
			found = 1;
			break;
		}
	}

	if (!found)
		return (-1);

	chn = i;

	/* Allocate area for buffer descriptors */
	channel->bd = (void *)kmem_alloc_contig(PAGE_SIZE, M_ZERO, 0, ~0,
	    PAGE_SIZE, 0, VM_MEMATTR_UNCACHEABLE);

	return (chn);
}
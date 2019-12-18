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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct sdma_softc {struct sdma_channel* channel; } ;
struct sdma_channel {scalar_t__ bd; scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdma_softc* sdma_sc ; 

int
sdma_free(int chn)
{
	struct sdma_channel *channel;
	struct sdma_softc *sc;

	sc = sdma_sc;

	channel = &sc->channel[chn];
	channel->in_use = 0;

	kmem_free((vm_offset_t)channel->bd, PAGE_SIZE);

	return (0);
}
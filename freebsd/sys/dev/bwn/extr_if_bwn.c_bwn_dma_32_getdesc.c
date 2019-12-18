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
struct bwn_dmadesc_meta {int dummy; } ;
struct bwn_dmadesc_generic {int dummy; } ;
struct bwn_dmadesc32 {int dummy; } ;
struct bwn_dma_ring {struct bwn_dmadesc32* dr_ring_descbase; struct bwn_dmadesc_meta* dr_meta; } ;

/* Variables and functions */

__attribute__((used)) static void
bwn_dma_32_getdesc(struct bwn_dma_ring *dr, int slot,
    struct bwn_dmadesc_generic **gdesc, struct bwn_dmadesc_meta **meta)
{
	struct bwn_dmadesc32 *desc;

	*meta = &(dr->dr_meta[slot]);
	desc = dr->dr_ring_descbase;
	desc = &(desc[slot]);

	*gdesc = (struct bwn_dmadesc_generic *)desc;
}
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
struct bwn_dma_ring {int dr_numslots; int dr_usedslot; TYPE_1__* dr_mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_dma_freeslot(struct bwn_dma_ring *dr)
{
	BWN_ASSERT_LOCKED(dr->dr_mac->mac_sc);

	return (dr->dr_numslots - dr->dr_usedslot);
}
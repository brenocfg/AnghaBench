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
struct bwn_dma_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_dma_cleanup (struct bwn_dma_ring*) ; 

__attribute__((used)) static void
bwn_dma_ringstop(struct bwn_dma_ring **dr)
{

	if (dr == NULL)
		return;

	bwn_dma_cleanup(*dr);
}
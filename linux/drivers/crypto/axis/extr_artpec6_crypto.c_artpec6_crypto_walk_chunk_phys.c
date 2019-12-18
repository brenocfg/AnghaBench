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
struct artpec6_crypto_walk {scalar_t__ offset; int /*<<< orphan*/  sg; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ sg_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_addr_t
artpec6_crypto_walk_chunk_phys(const struct artpec6_crypto_walk *awalk)
{
	return sg_phys(awalk->sg) + awalk->offset;
}
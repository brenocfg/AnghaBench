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

/* Variables and functions */
 int /*<<< orphan*/  linux_dma_obj_zone ; 
 int /*<<< orphan*/  linux_dma_trie_zone ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
linux_dma_uninit(void *arg)
{

	uma_zdestroy(linux_dma_obj_zone);
	uma_zdestroy(linux_dma_trie_zone);
}
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
struct linux_dma_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 void* linux_dma_obj_zone ; 
 void* linux_dma_trie_zone ; 
 int pctrie_node_size () ; 
 int /*<<< orphan*/ * pctrie_zone_init ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
linux_dma_init(void *arg)
{

	linux_dma_trie_zone = uma_zcreate("linux_dma_pctrie",
	    pctrie_node_size(), NULL, NULL, pctrie_zone_init, NULL,
	    UMA_ALIGN_PTR, 0);
	linux_dma_obj_zone = uma_zcreate("linux_dma_object",
	    sizeof(struct linux_dma_obj), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);

}
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
struct sprd_dma_chn {int /*<<< orphan*/ * cur_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprd_dma_clear_int (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  sprd_dma_stop_and_disable (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  sprd_dma_unset_uid (struct sprd_dma_chn*) ; 

__attribute__((used)) static void sprd_dma_stop(struct sprd_dma_chn *schan)
{
	sprd_dma_stop_and_disable(schan);
	sprd_dma_unset_uid(schan);
	sprd_dma_clear_int(schan);
	schan->cur_desc = NULL;
}
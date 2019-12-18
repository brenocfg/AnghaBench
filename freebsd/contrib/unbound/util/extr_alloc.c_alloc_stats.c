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
struct alloc_cache {scalar_t__ num_reg_blocks; scalar_t__ num_quar; scalar_t__ super; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_info (char*,char*,int,int) ; 

void 
alloc_stats(struct alloc_cache* alloc)
{
	log_info("%salloc: %d in cache, %d blocks.", alloc->super?"":"sup",
		(int)alloc->num_quar, (int)alloc->num_reg_blocks);
}
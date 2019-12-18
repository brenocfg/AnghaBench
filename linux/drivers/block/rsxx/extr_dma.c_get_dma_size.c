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
struct TYPE_2__ {int cnt; } ;
struct rsxx_dma {TYPE_1__ sub_page; } ;

/* Variables and functions */
 unsigned int RSXX_HW_BLK_SIZE ; 

__attribute__((used)) static unsigned int get_dma_size(struct rsxx_dma *dma)
{
	if (dma->sub_page.cnt)
		return dma->sub_page.cnt << 9;
	else
		return RSXX_HW_BLK_SIZE;
}
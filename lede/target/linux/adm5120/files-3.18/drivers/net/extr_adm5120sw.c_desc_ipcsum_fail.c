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
struct dma_desc {int misc; } ;

/* Variables and functions */
 int DESC_IPCSUM_FAIL ; 

__attribute__((used)) static inline int desc_ipcsum_fail(struct dma_desc *desc)
{
	return ((desc->misc & DESC_IPCSUM_FAIL) != 0);
}
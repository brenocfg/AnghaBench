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
typedef  int u32 ;
struct dma_desc {int misc; } ;

/* Variables and functions */
 int DESC_PKTLEN_MASK ; 
 int DESC_PKTLEN_SHIFT ; 

__attribute__((used)) static inline u32 desc_get_pktlen(struct dma_desc *desc)
{
	return (desc->misc >> DESC_PKTLEN_SHIFT) & DESC_PKTLEN_MASK;
}
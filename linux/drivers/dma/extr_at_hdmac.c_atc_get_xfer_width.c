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
typedef  size_t dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int atc_get_xfer_width(dma_addr_t src, dma_addr_t dst,
						size_t len)
{
	unsigned int width;

	if (!((src | dst  | len) & 3))
		width = 2;
	else if (!((src | dst | len) & 1))
		width = 1;
	else
		width = 0;

	return width;
}
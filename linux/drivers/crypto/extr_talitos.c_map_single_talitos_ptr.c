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
struct talitos_ptr {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  __map_single_talitos_ptr (struct device*,struct talitos_ptr*,unsigned int,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void map_single_talitos_ptr(struct device *dev,
				   struct talitos_ptr *ptr,
				   unsigned int len, void *data,
				   enum dma_data_direction dir)
{
	__map_single_talitos_ptr(dev, ptr, len, data, dir, 0);
}
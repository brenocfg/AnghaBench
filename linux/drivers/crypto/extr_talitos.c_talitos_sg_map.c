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
struct talitos_edesc {int dummy; } ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int talitos_sg_map_ext (struct device*,struct scatterlist*,unsigned int,struct talitos_edesc*,struct talitos_ptr*,int,unsigned int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int talitos_sg_map(struct device *dev, struct scatterlist *src,
			  unsigned int len, struct talitos_edesc *edesc,
			  struct talitos_ptr *ptr, int sg_count,
			  unsigned int offset, int tbl_off)
{
	return talitos_sg_map_ext(dev, src, len, edesc, ptr, sg_count, offset,
				  tbl_off, 0, false);
}
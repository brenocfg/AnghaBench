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
typedef  int /*<<< orphan*/  u32 ;
struct omap_des_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_des_read (struct omap_des_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_des_write (struct omap_des_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void omap_des_write_mask(struct omap_des_dev *dd, u32 offset,
					u32 value, u32 mask)
{
	u32 val;

	val = omap_des_read(dd, offset);
	val &= ~mask;
	val |= value;
	omap_des_write(dd, offset, val);
}
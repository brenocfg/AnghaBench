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
typedef  int /*<<< orphan*/  u16 ;
struct slim_device {int dummy; } ;

/* Variables and functions */
 int slim_read (struct slim_device*,int /*<<< orphan*/ ,size_t,void*) ; 

__attribute__((used)) static int regmap_slimbus_read(void *context, const void *reg, size_t reg_size,
			       void *val, size_t val_size)
{
	struct slim_device *sdev = context;

	return slim_read(sdev, *(u16 *)reg, val_size, val);
}
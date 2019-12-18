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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct slim_device {int dummy; } ;

/* Variables and functions */
 int slim_write (struct slim_device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int regmap_slimbus_write(void *context, const void *data, size_t count)
{
	struct slim_device *sdev = context;

	return slim_write(sdev, *(u16 *)data, count - 2, (u8 *)data + 2);
}
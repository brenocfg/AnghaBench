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
struct iicbus_ivar {uintptr_t addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct iicbus_ivar* IICBUS_IVAR (int /*<<< orphan*/ ) ; 
#define  IICBUS_IVAR_ADDR 128 

__attribute__((used)) static int
iicbus_read_ivar(device_t bus, device_t child, int which, uintptr_t *result)
{
	struct iicbus_ivar *devi = IICBUS_IVAR(child);

	switch (which) {
	default:
		return (EINVAL);
	case IICBUS_IVAR_ADDR:
		*result = devi->addr;
		break;
	}
	return (0);
}
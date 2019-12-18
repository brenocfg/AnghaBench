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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SYS_RES_IRQ ; 
 int /*<<< orphan*/  cpu_hardirq_rman ; 
 struct resource* rman_reserve_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
cpu_alloc_resource(device_t dev, device_t child, int type, int *rid,
		   rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct resource *res;

	if (type != SYS_RES_IRQ)
		return (NULL);
	res = rman_reserve_resource(&cpu_hardirq_rman, start, end, count, 0,
				    child);
	return (res);
}
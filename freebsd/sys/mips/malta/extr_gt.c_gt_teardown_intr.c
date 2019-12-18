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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_TEARDOWN_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gt_teardown_intr(device_t dev, device_t child, struct resource *res,
    void *cookie)
{
	return (BUS_TEARDOWN_INTR(device_get_parent(dev), child, res, cookie));
}
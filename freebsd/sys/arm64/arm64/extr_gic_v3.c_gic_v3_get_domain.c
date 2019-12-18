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
struct gic_v3_devinfo {int gic_domain; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 struct gic_v3_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_get_domain(device_t dev, device_t child, int *domain)
{
	struct gic_v3_devinfo *di;

	di = device_get_ivars(child);
	if (di->gic_domain < 0)
		return (ENOENT);

	*domain = di->gic_domain;
	return (0);
}
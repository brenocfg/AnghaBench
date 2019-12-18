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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int mvneta_attach (int /*<<< orphan*/ ) ; 
 int mvneta_fdt_phy_acquire (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvneta_fdt_attach(device_t dev)
{
	int err;

	/* Try to fetch PHY information from FDT */
	err = mvneta_fdt_phy_acquire(dev);
	if (err != 0)
		return (err);

	return (mvneta_attach(dev));
}
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
 int nvdimm_e820_remove_spas (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvdimm_e820_detach(device_t dev)
{
	int error;

	error = nvdimm_e820_remove_spas(dev);
	return (error);
}
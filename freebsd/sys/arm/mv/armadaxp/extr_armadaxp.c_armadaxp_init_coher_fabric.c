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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  COHER_FABRIC_CONF ; 
 int /*<<< orphan*/  COHER_FABRIC_CTRL ; 
 int platform_get_ncpus () ; 
 int read_coher_fabric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_coher_fabric (int /*<<< orphan*/ ,int) ; 

void
armadaxp_init_coher_fabric(void)
{
	uint32_t val, cpus, mask;

	cpus = platform_get_ncpus();
	mask = (1 << cpus) - 1;
	val = read_coher_fabric(COHER_FABRIC_CTRL);
	val |= (mask << 24);
	write_coher_fabric(COHER_FABRIC_CTRL, val);

	val = read_coher_fabric(COHER_FABRIC_CONF);
	val |= (mask << 24);
	val |= (1 << 15);
	write_coher_fabric(COHER_FABRIC_CONF, val);
}
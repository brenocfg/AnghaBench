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

/* Variables and functions */
 int /*<<< orphan*/  COHER_FABRIC_CONF ; 
 int read_coher_fabric (int /*<<< orphan*/ ) ; 

int
platform_get_ncpus(void)
{
#if !defined(SMP)
	return (1);
#else
	return ((read_coher_fabric(COHER_FABRIC_CONF) & 0xf) + 1);
#endif
}
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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_DEFAULT_ENUM_SIZE ; 
 scalar_t__ resource_long_value (char*,int /*<<< orphan*/ ,char*,long*) ; 

__attribute__((used)) static bus_size_t
bcm_get_bus_size(void)
{
	long msize;

	if (resource_long_value("bhnd", 0, "msize", &msize) == 0)
		return ((u_long)msize);

	return (BHND_DEFAULT_ENUM_SIZE);
}
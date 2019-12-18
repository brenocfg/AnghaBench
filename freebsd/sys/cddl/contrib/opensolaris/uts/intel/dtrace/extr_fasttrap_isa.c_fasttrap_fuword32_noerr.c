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
 int fasttrap_fuword32 (void const*) ; 

__attribute__((used)) static uint32_t
fasttrap_fuword32_noerr(const void *uaddr)
{
	uint32_t ret;

	if ((ret = fasttrap_fuword32(uaddr)) != -1)
		return (ret);

	return (0);
}
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
 uintptr_t fasttrap_fulword (void const*) ; 

__attribute__((used)) static uintptr_t
fasttrap_fulword_noerr(const void *uaddr)
{
	uintptr_t ret;

	if ((ret = fasttrap_fulword(uaddr)) != -1)
		return (ret);

	return (0);
}
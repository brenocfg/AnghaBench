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
 int /*<<< orphan*/  getpagesize () ; 
 scalar_t__ posix_memalign (void**,int /*<<< orphan*/ ,size_t) ; 

void *
valloc(size_t i)
{
	void	*ret;

	if (posix_memalign(&ret, getpagesize(), i) != 0)
		ret = NULL;

	return ret;
}
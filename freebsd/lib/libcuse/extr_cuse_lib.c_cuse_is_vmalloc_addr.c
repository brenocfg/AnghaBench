#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* ptr; } ;

/* Variables and functions */
 int CUSE_ALLOC_UNIT_MAX ; 
 int /*<<< orphan*/  CUSE_LOCK () ; 
 int /*<<< orphan*/  CUSE_UNLOCK () ; 
 TYPE_1__* a_cuse ; 
 scalar_t__ f_cuse ; 

int
cuse_is_vmalloc_addr(void *ptr)
{
	int n;

	if (f_cuse < 0 || ptr == NULL)
		return (0);		/* false */

	CUSE_LOCK();
	for (n = 0; n != CUSE_ALLOC_UNIT_MAX; n++) {
		if (a_cuse[n].ptr == ptr)
			break;
	}
	CUSE_UNLOCK();

	return (n != CUSE_ALLOC_UNIT_MAX);
}
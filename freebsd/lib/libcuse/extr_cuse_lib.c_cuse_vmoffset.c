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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int size; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int CUSE_ALLOC_PAGES_MAX ; 
 int CUSE_ALLOC_UNIT_MAX ; 
 int /*<<< orphan*/  CUSE_LOCK () ; 
 int /*<<< orphan*/  CUSE_UNLOCK () ; 
 unsigned long PAGE_SIZE ; 
 TYPE_1__* a_cuse ; 

unsigned long
cuse_vmoffset(void *_ptr)
{
	uint8_t *ptr_min;
	uint8_t *ptr_max;
	uint8_t *ptr = _ptr;
	unsigned long remainder;
	int n;

	CUSE_LOCK();
	for (n = 0; n != CUSE_ALLOC_UNIT_MAX; n++) {
		if (a_cuse[n].ptr == NULL)
			continue;

		ptr_min = a_cuse[n].ptr;
		ptr_max = a_cuse[n].ptr + a_cuse[n].size - 1;

		if ((ptr >= ptr_min) && (ptr <= ptr_max)) {

			CUSE_UNLOCK();

			remainder = (ptr - ptr_min);

			remainder -= remainder % PAGE_SIZE;

			return ((n * PAGE_SIZE * CUSE_ALLOC_PAGES_MAX) + remainder);
		}
	}
	CUSE_UNLOCK();

	return (0x80000000UL);		/* failure */
}
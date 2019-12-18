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
struct cuse_alloc_info {int page_count; int alloc_nr; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {int size; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int CUSE_ALLOC_PAGES_MAX ; 
 int CUSE_ALLOC_UNIT_MAX ; 
 int /*<<< orphan*/  CUSE_IOCTL_ALLOC_MEMORY ; 
 int /*<<< orphan*/  CUSE_IOCTL_FREE_MEMORY ; 
 int /*<<< orphan*/  CUSE_LOCK () ; 
 int /*<<< orphan*/  CUSE_UNLOCK () ; 
 scalar_t__ EBUSY ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PAGE_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 TYPE_1__* a_cuse ; 
 scalar_t__ errno ; 
 scalar_t__ f_cuse ; 
 int howmany (int,int) ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,struct cuse_alloc_info*) ; 
 int /*<<< orphan*/  memset (struct cuse_alloc_info*,int /*<<< orphan*/ ,int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,scalar_t__,int) ; 

void   *
cuse_vmalloc(int size)
{
	struct cuse_alloc_info info;
	void *ptr;
	int error;
	int n;

	if (f_cuse < 0)
		return (NULL);

	memset(&info, 0, sizeof(info));

	if (size < 1)
		return (NULL);

	info.page_count = howmany(size, PAGE_SIZE);

	CUSE_LOCK();
	for (n = 0; n != CUSE_ALLOC_UNIT_MAX; n++) {

		if (a_cuse[n].ptr != NULL)
			continue;

		a_cuse[n].ptr = ((uint8_t *)1);	/* reserve */
		a_cuse[n].size = 0;

		CUSE_UNLOCK();

		info.alloc_nr = n;

		error = ioctl(f_cuse, CUSE_IOCTL_ALLOC_MEMORY, &info);

		if (error) {

			CUSE_LOCK();

			a_cuse[n].ptr = NULL;

			if (errno == EBUSY)
				continue;
			else
				break;
		}
		ptr = mmap(NULL, info.page_count * PAGE_SIZE,
		    PROT_READ | PROT_WRITE,
		    MAP_SHARED, f_cuse, CUSE_ALLOC_PAGES_MAX *
		    PAGE_SIZE * n);

		if (ptr == MAP_FAILED) {

			error = ioctl(f_cuse, CUSE_IOCTL_FREE_MEMORY, &info);

			if (error) {
				/* ignore */
			}
			CUSE_LOCK();

			a_cuse[n].ptr = NULL;

			break;
		}
		CUSE_LOCK();
		a_cuse[n].ptr = ptr;
		a_cuse[n].size = size;
		CUSE_UNLOCK();

		return (ptr);		/* success */
	}
	CUSE_UNLOCK();
	return (NULL);			/* failure */
}
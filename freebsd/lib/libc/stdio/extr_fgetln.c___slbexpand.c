#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t _size; void* _base; } ;
struct TYPE_5__ {TYPE_1__ _lb; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  errno ; 
 void* realloc (void*,size_t) ; 

int
__slbexpand(FILE *fp, size_t newsize)
{
	void *p;

	if (fp->_lb._size >= newsize)
		return (0);
	if (newsize > INT_MAX) {
		errno = ENOMEM;
		return (-1);
	}
	if ((p = realloc(fp->_lb._base, newsize)) == NULL)
		return (-1);
	fp->_lb._base = p;
	fp->_lb._size = newsize;
	return (0);
}
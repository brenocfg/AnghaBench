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
 scalar_t__ MANDOCLEVEL_SYSERR ; 
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 

void *
mandoc_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = calloc(num, size);
	if (ptr == NULL)
		err((int)MANDOCLEVEL_SYSERR, NULL);
	return ptr;
}
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
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void *
xrealloc(void *ptr, size_t nbytes)
{
	void *p = realloc(ptr, nbytes);

	if (p == NULL)
		errx(EX_OSERR, "out of memory");
	return p;
}
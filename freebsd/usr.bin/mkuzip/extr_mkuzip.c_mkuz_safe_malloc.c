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
 int /*<<< orphan*/  err (int,char*) ; 
 void* malloc (size_t) ; 

void *
mkuz_safe_malloc(size_t size)
{
	void *retval;

	retval = malloc(size);
	if (retval == NULL) {
		err(1, "can't allocate memory");
		/* Not reached */
	}
	return retval;
}
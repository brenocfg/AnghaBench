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
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 void* malloc (int) ; 

__attribute__((used)) static void *
do_malloc(int size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		errx(EX_SOFTWARE, "Could not allocate memory");
	return (ptr);
}
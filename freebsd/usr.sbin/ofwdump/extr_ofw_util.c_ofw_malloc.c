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
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 void* malloc (int) ; 

__attribute__((used)) static void *
ofw_malloc(int size)
{
	void *p;

	if ((p = malloc(size)) == NULL)
		err(EX_OSERR, "malloc() failed");
	return (p);
}
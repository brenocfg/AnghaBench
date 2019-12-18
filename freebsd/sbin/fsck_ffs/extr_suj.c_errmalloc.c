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
 void* Malloc (size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void *
errmalloc(size_t n)
{
	void *a;

	a = Malloc(n);
	if (a == NULL)
		err(EX_OSERR, "malloc(%zu)", n);
	return (a);
}
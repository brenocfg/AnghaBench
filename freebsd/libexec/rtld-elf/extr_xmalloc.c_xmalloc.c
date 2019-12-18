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
 int /*<<< orphan*/  STDERR_FILENO ; 
 void* __crt_malloc (size_t) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  rtld_fdputstr (int /*<<< orphan*/ ,char*) ; 

void *
xmalloc(size_t size)
{

	void *p;

	p = __crt_malloc(size);
	if (p == NULL) {
		rtld_fdputstr(STDERR_FILENO, "Out of memory\n");
		_exit(1);
	}
	return (p);
}
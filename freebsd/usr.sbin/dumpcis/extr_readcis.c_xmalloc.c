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
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 void* malloc (int) ; 

__attribute__((used)) static void *
xmalloc(int sz)
{
	void   *p;

	sz = (sz + 7) & ~7;
	p = malloc(sz);
	if (p == NULL)
		errx(1, "malloc");
	bzero(p, sz);
	return (p);
}
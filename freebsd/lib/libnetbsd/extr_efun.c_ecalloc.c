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
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  efunc (int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (int,char*,size_t,size_t) ; 

void *
ecalloc(size_t n, size_t s)
{
	void *p = calloc(n, s);
	if (p == NULL && n != 0 && s != 0)
		(*efunc)(1, "Cannot allocate %zu blocks of size %zu", n, s);
	return p;
}
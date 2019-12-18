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
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static void *
xmalloc(size_t size)
{
	void *m;

	if ((m = calloc(1, size)) == NULL)
		errx(1, "memory allocation failure");
	return (m);
}
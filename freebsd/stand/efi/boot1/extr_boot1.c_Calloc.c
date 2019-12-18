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
 void* Malloc (size_t,char const*,int) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 

void *
Calloc(size_t n1, size_t n2, const char *file, int line)
{
	size_t bytes;
	void *res;

	bytes = n1 * n2;
	if ((res = Malloc(bytes, file, line)) != NULL)
		bzero(res, bytes);

	return (res);
}
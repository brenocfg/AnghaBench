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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  logbad (int,char*,int /*<<< orphan*/ ,char const*) ; 
 void* malloc (size_t) ; 

void *
rtmalloc(size_t size,
	 const char *msg)
{
	void *p = malloc(size);
	if (p == NULL)
		logbad(1,"malloc(%lu) failed in %s", (u_long)size, msg);
	return p;
}
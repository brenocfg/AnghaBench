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
 int exhaust_named_child (void*) ; 
 int fdlimit_set (void*) ; 

__attribute__((used)) static int
fdlimit_named_child(void *arg)
{
	int stat;

	stat = fdlimit_set(arg);
	if (stat == 0)
		stat = exhaust_named_child(arg);
	return (stat);
}
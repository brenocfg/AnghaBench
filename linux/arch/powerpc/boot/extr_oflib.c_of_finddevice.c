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
 scalar_t__ of_call_prom (char*,int,int,char const*) ; 

void *of_finddevice(const char *name)
{
	return (void *) (unsigned long) of_call_prom("finddevice", 1, 1, name);
}
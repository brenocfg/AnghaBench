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
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int g_io_getattr (char const*,struct g_consumer*,int*,void*) ; 

int
g_getattr__(const char *attr, struct g_consumer *cp, void *var, int len)
{
	int error, i;

	i = len;
	error = g_io_getattr(attr, cp, &i, var);
	if (error)
		return (error);
	if (i != len)
		return (EINVAL);
	return (0);
}
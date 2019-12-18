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
typedef  double time_t ;

/* Variables and functions */

__attribute__((used)) static const char *
tformat(void)
{
	if (0.5 == (time_t) 0.5) {	/* floating */
		if (sizeof (time_t) > sizeof (double))
			return "%Lg";
		return "%g";
	}
	if (0 > (time_t) -1) {		/* signed */
		if (sizeof (time_t) > sizeof (long))
			return "%lld";
		if (sizeof (time_t) > sizeof (int))
			return "%ld";
		return "%d";
	}
	if (sizeof (time_t) > sizeof (unsigned long))
		return "%llu";
	if (sizeof (time_t) > sizeof (unsigned int))
		return "%lu";
	return "%u";
}
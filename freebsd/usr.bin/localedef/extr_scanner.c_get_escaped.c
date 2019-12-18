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

int
get_escaped(int c)
{
	switch (c) {
	case 'n':
		return ('\n');
	case 'r':
		return ('\r');
	case 't':
		return ('\t');
	case 'f':
		return ('\f');
	case 'v':
		return ('\v');
	case 'b':
		return ('\b');
	case 'a':
		return ('\a');
	default:
		return (c);
	}
}
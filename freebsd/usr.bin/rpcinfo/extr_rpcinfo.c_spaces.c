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
typedef  int /*<<< orphan*/  space_array ;

/* Variables and functions */

__attribute__((used)) static char *
spaces(int howmany)
{
	static char space_array[] =		/* 64 spaces */
	"                                                                ";

	if (howmany <= 0 || howmany > sizeof (space_array)) {
		return ("");
	}
	return (&space_array[sizeof (space_array) - howmany - 1]);
}
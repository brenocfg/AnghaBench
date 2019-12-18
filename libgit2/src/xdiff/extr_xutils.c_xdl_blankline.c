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
 long XDF_WHITESPACE_FLAGS ; 
 scalar_t__ XDL_ISSPACE (char const) ; 

int xdl_blankline(const char *line, long size, long flags)
{
	long i;

	if (!(flags & XDF_WHITESPACE_FLAGS))
		return (size <= 1);

	for (i = 0; i < size && XDL_ISSPACE(line[i]); i++)
		;

	return (i == size);
}
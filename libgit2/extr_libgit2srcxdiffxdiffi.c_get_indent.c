#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {long size; char* ptr; } ;
typedef  TYPE_1__ xrecord_t ;

/* Variables and functions */
 int MAX_INDENT ; 
 int /*<<< orphan*/  XDL_ISSPACE (char) ; 

__attribute__((used)) static int get_indent(xrecord_t *rec)
{
	long i;
	int ret = 0;

	for (i = 0; i < rec->size; i++) {
		char c = rec->ptr[i];

		if (!XDL_ISSPACE(c))
			return ret;
		else if (c == ' ')
			ret += 1;
		else if (c == '\t')
			ret += 8 - ret % 8;
		/* ignore other whitespace characters */

		if (ret >= MAX_INDENT)
			return MAX_INDENT;
	}

	/* The line contains only whitespace. */
	return -1;
}
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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int fst_read_next_int_param(const char *params, Boolean *valid, char **endp)
{
	int ret = -1;
	const char *curp;

	*valid = FALSE;
	*endp = (char *) params;
	curp = params;
	if (*curp) {
		ret = (int) strtol(curp, endp, 0);
		if (!**endp || isspace(**endp))
			*valid = TRUE;
	}

	return ret;
}
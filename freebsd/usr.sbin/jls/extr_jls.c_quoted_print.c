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
 int PRINT_QUOTED ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 

__attribute__((used)) static void
quoted_print(int pflags, char *name, char *value)
{
	int qc;
	char *p = value;
	char *param_name_value;

	/* An empty string needs quoting. */
	if (!*p) {
		asprintf(&param_name_value, "{k:%s}{d:%s/\"\"}", name, name);
		xo_emit(param_name_value);
		free(param_name_value);
		return;
	}

	asprintf(&param_name_value, "{:%s/%%s}", name);
	/*
	 * The value will be surrounded by quotes if it contains spaces
	 * or quotes.
	 */
	qc = strchr(p, '\'') ? '"'
		: strchr(p, '"') ? '\''
		: strchr(p, ' ') || strchr(p, '\t') ? '"'
		: 0;

	if (qc && pflags & PRINT_QUOTED)
		xo_emit("{P:/%c}", qc);

	xo_emit(param_name_value, value);

	free(param_name_value);

	if (qc && pflags & PRINT_QUOTED)
		xo_emit("{P:/%c}", qc);
}
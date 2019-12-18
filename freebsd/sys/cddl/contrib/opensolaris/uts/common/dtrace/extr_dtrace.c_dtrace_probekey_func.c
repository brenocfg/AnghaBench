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
typedef  int /*<<< orphan*/  dtrace_probekey_f ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_match_glob ; 
 int /*<<< orphan*/  dtrace_match_nul ; 
 int /*<<< orphan*/  dtrace_match_string ; 

__attribute__((used)) static dtrace_probekey_f *
dtrace_probekey_func(const char *p)
{
	char c;

	if (p == NULL || *p == '\0')
		return (&dtrace_match_nul);

	while ((c = *p++) != '\0') {
		if (c == '[' || c == '?' || c == '*' || c == '\\')
			return (&dtrace_match_glob);
	}

	return (&dtrace_match_string);
}
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
 int /*<<< orphan*/  TR2_ENVVAR_NORMAL_BRIEF ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int git_parse_maybe_bool (char*) ; 
 int tr2_dst_trace_want (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_normal ; 
 int tr2env_normal_brief ; 

__attribute__((used)) static int fn_init(void)
{
	int want = tr2_dst_trace_want(&tr2dst_normal);
	int want_brief;
	char *brief;

	if (!want)
		return want;

	brief = getenv(TR2_ENVVAR_NORMAL_BRIEF);
	if (brief && *brief &&
	    ((want_brief = git_parse_maybe_bool(brief)) != -1))
		tr2env_normal_brief = want_brief;

	return want;
}
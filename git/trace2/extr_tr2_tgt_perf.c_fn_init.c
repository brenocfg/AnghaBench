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
 int /*<<< orphan*/  TR2_DOTS_BUFFER_SIZE ; 
 int /*<<< orphan*/  TR2_SYSENV_PERF_BRIEF ; 
 int /*<<< orphan*/  dots ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  strbuf_addchars (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int tr2_dst_trace_want (int /*<<< orphan*/ *) ; 
 char* tr2_sysenv_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2dst_perf ; 
 int tr2env_perf_be_brief ; 

__attribute__((used)) static int fn_init(void)
{
	int want = tr2_dst_trace_want(&tr2dst_perf);
	int want_brief;
	const char *brief;

	if (!want)
		return want;

	strbuf_addchars(&dots, '.', TR2_DOTS_BUFFER_SIZE);

	brief = tr2_sysenv_get(TR2_SYSENV_PERF_BRIEF);
	if (brief && *brief &&
	    ((want_brief = git_parse_maybe_bool(brief)) != -1))
		tr2env_perf_be_brief = want_brief;

	return want;
}
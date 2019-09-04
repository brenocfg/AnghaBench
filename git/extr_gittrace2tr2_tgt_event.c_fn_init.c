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
 int /*<<< orphan*/  TR2_ENVVAR_EVENT_BRIEF ; 
 int /*<<< orphan*/  TR2_ENVVAR_EVENT_NESTING ; 
 int atoi (char*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int tr2_dst_trace_want (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2dst_event ; 
 int tr2env_event_brief ; 
 int tr2env_event_nesting_wanted ; 

__attribute__((used)) static int fn_init(void)
{
	int want = tr2_dst_trace_want(&tr2dst_event);
	int want_nesting;
	int want_brief;
	char *nesting;
	char *brief;

	if (!want)
		return want;

	nesting = getenv(TR2_ENVVAR_EVENT_NESTING);
	if (nesting && ((want_nesting = atoi(nesting)) > 0))
		tr2env_event_nesting_wanted = want_nesting;

	brief = getenv(TR2_ENVVAR_EVENT_BRIEF);
	if (brief && ((want_brief = atoi(brief)) > 0))
		tr2env_event_brief = want_brief;

	return want;
}
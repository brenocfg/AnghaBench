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
#define  LOG_REFS_ALWAYS 129 
#define  LOG_REFS_NORMAL 128 
 int log_all_ref_updates ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int should_autocreate_reflog(const char *refname)
{
	switch (log_all_ref_updates) {
	case LOG_REFS_ALWAYS:
		return 1;
	case LOG_REFS_NORMAL:
		return starts_with(refname, "refs/heads/") ||
			starts_with(refname, "refs/remotes/") ||
			starts_with(refname, "refs/notes/") ||
			!strcmp(refname, "HEAD");
	default:
		return 0;
	}
}
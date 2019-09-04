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
struct print_payload {int options; int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 unsigned int GIT_STATUS_WT_MODIFIED ; 
 unsigned int GIT_STATUS_WT_NEW ; 
 int SKIP ; 
 scalar_t__ git_status_file (unsigned int*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

int print_matched_cb(const char *path, const char *matched_pathspec, void *payload)
{
	struct print_payload p = *(struct print_payload*)(payload);
	int ret;
	unsigned status;
	(void)matched_pathspec;

	/* Get the file status */
	if (git_status_file(&status, p.repo, path)) {
		return -1;
	}

	if ((status & GIT_STATUS_WT_MODIFIED) || (status & GIT_STATUS_WT_NEW)) {
		printf("add '%s'\n", path);
		ret = 0;
	} else {
		ret = 1;
	}

	if ((p.options & SKIP)) {
		ret = 1;
	}

	return ret;
}
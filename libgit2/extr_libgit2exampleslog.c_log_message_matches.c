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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 char* git_commit_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char const*) ; 

__attribute__((used)) static int log_message_matches(const git_commit *commit, const char *filter) {
	const char *message = NULL;

	if (filter == NULL)
		return 1;

	if ((message = git_commit_message(commit)) != NULL &&
		strstr(message, filter) != NULL)
		return 1;

	return 0;
}
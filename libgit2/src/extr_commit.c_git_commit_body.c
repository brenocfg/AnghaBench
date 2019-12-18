#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* body; } ;
typedef  TYPE_1__ git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git__isspace (char const) ; 
 char const* git__strndup (char const*,int) ; 
 char* git_commit_message (TYPE_1__*) ; 
 int strlen (char const*) ; 

const char *git_commit_body(git_commit *commit)
{
	const char *msg, *end;

	assert(commit);

	if (!commit->body) {
		/* search for end of summary */
		for (msg = git_commit_message(commit); *msg; ++msg)
			if (msg[0] == '\n' && (!msg[1] || msg[1] == '\n'))
				break;

		/* trim leading and trailing whitespace */
		for (; *msg; ++msg)
			if (!git__isspace(*msg))
				break;
		for (end = msg + strlen(msg) - 1; msg <= end; --end)
			if (!git__isspace(*end))
				break;

		if (*msg)
			commit->body = git__strndup(msg, end - msg + 1);
	}

	return commit->body;
}
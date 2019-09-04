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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_attach (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int note_get_default_ref (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int git_note_default_ref(git_buf *out, git_repository *repo)
{
	char *default_ref;
	int error;

	assert(out && repo);

	git_buf_sanitize(out);

	if ((error = note_get_default_ref(&default_ref, repo)) < 0)
		return error;

	git_buf_attach(out, default_ref, strlen(default_ref));
	return 0;
}
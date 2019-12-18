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
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int git_signature__parse (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *,char) ; 
 int strlen (char const*) ; 

int git_signature_from_buffer(git_signature **out, const char *buf)
{
	git_signature *sig;
	const char *buf_end;
	int error;

	assert(out && buf);

	*out = NULL;

	sig = git__calloc(1, sizeof(git_signature));
	GIT_ERROR_CHECK_ALLOC(sig);

	buf_end = buf + strlen(buf);
	error = git_signature__parse(sig, &buf, buf_end, NULL, '\0');

	if (error)
		git__free(sig);
	else
		*out = sig;

	return error;
}
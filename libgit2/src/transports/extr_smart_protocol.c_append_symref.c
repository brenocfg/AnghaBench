#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {scalar_t__ klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CAP_SYMREF ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 scalar_t__ GIT_ERROR_NOMEMORY ; 
 int /*<<< orphan*/ * git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_put (int /*<<< orphan*/ *,char const*,int) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_refspec__dispose (int /*<<< orphan*/ *) ; 
 int git_refspec__parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int append_symref(const char **out, git_vector *symrefs, const char *ptr)
{
	int error;
	const char *end;
	git_buf buf = GIT_BUF_INIT;
	git_refspec *mapping = NULL;

	ptr += strlen(GIT_CAP_SYMREF);
	if (*ptr != '=')
		goto on_invalid;

	ptr++;
	if (!(end = strchr(ptr, ' ')) &&
	    !(end = strchr(ptr, '\0')))
		goto on_invalid;

	if ((error = git_buf_put(&buf, ptr, end - ptr)) < 0)
		return error;

	/* symref mapping has refspec format */
	mapping = git__calloc(1, sizeof(git_refspec));
	GIT_ERROR_CHECK_ALLOC(mapping);

	error = git_refspec__parse(mapping, git_buf_cstr(&buf), true);
	git_buf_dispose(&buf);

	/* if the error isn't OOM, then it's a parse error; let's use a nicer message */
	if (error < 0) {
		if (git_error_last()->klass != GIT_ERROR_NOMEMORY)
			goto on_invalid;

		git__free(mapping);
		return error;
	}

	if ((error = git_vector_insert(symrefs, mapping)) < 0)
		return error;

	*out = end;
	return 0;

on_invalid:
	git_error_set(GIT_ERROR_NET, "remote sent invalid symref");
	git_refspec__dispose(mapping);
	git__free(mapping);
	return -1;
}
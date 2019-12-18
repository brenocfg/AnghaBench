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
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_5__ {char* ptr; void* size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int apply_gitbuf (TYPE_1__*,char const*,TYPE_1__*,char const*,char const*,int /*<<< orphan*/  const*) ; 
 void* strlen (char const*) ; 

__attribute__((used)) static int apply_buf(
	const char *old,
	const char *oldname,
	const char *new,
	const char *newname,
	const char *patch_expected,
	const git_diff_options *diff_opts)
{
	git_buf o = GIT_BUF_INIT, n = GIT_BUF_INIT,
		*optr = NULL, *nptr = NULL;

	if (old) {
		o.ptr = (char *)old;
		o.size = strlen(old);
		optr = &o;
	}

	if (new) {
		n.ptr = (char *)new;
		n.size = strlen(new);
		nptr = &n;
	}

	return apply_gitbuf(optr, oldname, nptr, newname, patch_expected, diff_opts);
}
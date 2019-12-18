#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; int /*<<< orphan*/  re; } ;
typedef  TYPE_1__ git_diff_driver_pattern ;
struct TYPE_11__ {int /*<<< orphan*/  fn_patterns; } ;
typedef  TYPE_2__ git_diff_driver ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int REG_NEGATE ; 
 TYPE_1__* git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_array_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_buf_set (TYPE_3__*,char const*,int) ; 
 int git_buf_sets (TYPE_3__*,char const*) ; 
 int git_regexp_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int diff_driver_add_patterns(
	git_diff_driver *drv, const char *regex_str, int regex_flags)
{
	int error = 0;
	const char *scan, *end;
	git_diff_driver_pattern *pat = NULL;
	git_buf buf = GIT_BUF_INIT;

	for (scan = regex_str; scan; scan = end) {
		/* get pattern to fill in */
		if ((pat = git_array_alloc(drv->fn_patterns)) == NULL) {
			return -1;
		}

		pat->flags = regex_flags;
		if (*scan == '!') {
			pat->flags |= REG_NEGATE;
			++scan;
		}

		if ((end = strchr(scan, '\n')) != NULL) {
			error = git_buf_set(&buf, scan, end - scan);
			end++;
		} else {
			error = git_buf_sets(&buf, scan);
		}
		if (error < 0)
			break;

		if ((error = git_regexp_compile(&pat->re, buf.ptr, regex_flags)) != 0) {
			/*
			 * TODO: issue a warning
			 */
		}
	}

	if (error && pat != NULL)
		(void)git_array_pop(drv->fn_patterns); /* release last item */
	git_buf_dispose(&buf);

	/* We want to ignore bad patterns, so return success regardless */
	return 0;
}
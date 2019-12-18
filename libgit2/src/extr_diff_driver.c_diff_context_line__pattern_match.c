#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ git_regmatch ;
struct TYPE_14__ {int flags; int /*<<< orphan*/  re; } ;
typedef  TYPE_2__ git_diff_driver_pattern ;
struct TYPE_15__ {int /*<<< orphan*/  fn_patterns; } ;
typedef  TYPE_3__ git_diff_driver ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 int REG_NEGATE ; 
 TYPE_2__* git_array_get (int /*<<< orphan*/ ,size_t) ; 
 size_t git_array_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_4__*,scalar_t__) ; 
 scalar_t__ git_buf_cstr (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  git_regexp_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static int diff_context_line__pattern_match(
	git_diff_driver *driver, git_buf *line)
{
	size_t i, maxi = git_array_size(driver->fn_patterns);
	git_regmatch pmatch[2];

	for (i = 0; i < maxi; ++i) {
		git_diff_driver_pattern *pat = git_array_get(driver->fn_patterns, i);

		if (!git_regexp_search(&pat->re, line->ptr, 2, pmatch)) {
			if (pat->flags & REG_NEGATE)
				return false;

			/* use pmatch data to trim line data */
			i = (pmatch[1].start >= 0) ? 1 : 0;
			git_buf_consume(line, git_buf_cstr(line) + pmatch[i].start);
			git_buf_truncate(line, pmatch[i].end - pmatch[i].start);
			git_buf_rtrim(line);

			return true;
		}
	}

	return false;
}
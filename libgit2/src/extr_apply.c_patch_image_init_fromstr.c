#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lines; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ patch_image ;
typedef  int /*<<< orphan*/  git_diff_line ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * git_pool_mallocz (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  patch_line_init (int /*<<< orphan*/ *,char const*,int,int) ; 

__attribute__((used)) static int patch_image_init_fromstr(
	patch_image *out, const char *in, size_t in_len)
{
	git_diff_line *line;
	const char *start, *end;

	memset(out, 0x0, sizeof(patch_image));

	git_pool_init(&out->pool, sizeof(git_diff_line));

	for (start = in; start < in + in_len; start = end) {
		end = memchr(start, '\n', in_len - (start - in));

		if (end == NULL)
			end = in + in_len;

		else if (end < in + in_len)
			end++;

		line = git_pool_mallocz(&out->pool, 1);
		GIT_ERROR_CHECK_ALLOC(line);

		if (git_vector_insert(&out->lines, line) < 0)
			return -1;

		patch_line_init(line, start, (end - start), (start - in));
	}

	return 0;
}
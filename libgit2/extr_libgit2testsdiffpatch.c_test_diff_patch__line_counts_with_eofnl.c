#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_10__ {char* ptr; int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  check_single_patch_stats (int /*<<< orphan*/ ,int,int,int,int,size_t*,char const*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_1__*,char const*) ; 
 char* git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_find (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_reinit_filesystem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

void test_diff_patch__line_counts_with_eofnl(void)
{
	git_config *cfg;
	git_buf content = GIT_BUF_INIT;
	const char *end;
	git_index *index;
	const char *expected =
		/* below is pasted output of 'git diff' with fn context removed */
		"diff --git a/songof7cities.txt b/songof7cities.txt\n"
		"index 378a7d9..3d0154e 100644\n"
		"--- a/songof7cities.txt\n"
		"+++ b/songof7cities.txt\n"
		"@@ -42,7 +42,7 @@ With peoples undefeated of the dark, enduring blood.\n"
		" \n"
		" To the sound of trumpets shall their seed restore my Cities\n"
		" Wealthy and well-weaponed, that once more may I behold\n"
		"-All the world go softly when it walks before my Cities,\n"
		"+#All the world go softly when it walks before my Cities,\n"
		" And the horses and the chariots fleeing from them as of old!\n"
		" \n"
		"   -- Rudyard Kipling\n"
		"\\ No newline at end of file\n";
	size_t expected_sizes[3] = { 115, 119 + 115 + 114, 119 + 115 + 114 + 71 };

	g_repo = cl_git_sandbox_init("renames");

	cl_git_pass(git_config_new(&cfg));
	git_repository_set_config(g_repo, cfg);
	git_config_free(cfg);

	git_repository_reinit_filesystem(g_repo, false);

	cl_git_pass(git_futils_readbuffer(&content, "renames/songof7cities.txt"));

	/* remove first line */

	end = git_buf_cstr(&content) + git_buf_find(&content, '\n') + 1;
	git_buf_consume(&content, end);
	cl_git_rewritefile("renames/songof7cities.txt", content.ptr);

	check_single_patch_stats(g_repo, 1, 0, 1, 3, NULL, NULL);

	/* remove trailing whitespace */

	git_buf_rtrim(&content);
	cl_git_rewritefile("renames/songof7cities.txt", content.ptr);

	check_single_patch_stats(g_repo, 2, 1, 2, 6, NULL, NULL);

	/* add trailing whitespace */

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_add_bypath(index, "songof7cities.txt"));
	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_git_pass(git_buf_putc(&content, '\n'));
	cl_git_rewritefile("renames/songof7cities.txt", content.ptr);

	check_single_patch_stats(g_repo, 1, 1, 1, 3, NULL, NULL);

	/* no trailing whitespace as context line */

	{
		/* walk back a couple lines, make space and insert char */
		char *scan = content.ptr + content.size;
		int i;

		for (i = 0; i < 5; ++i) {
			for (--scan; scan > content.ptr && *scan != '\n'; --scan)
				/* seek to prev \n */;
		}
		cl_assert(scan > content.ptr);

		/* overwrite trailing \n with right-shifted content */
		memmove(scan + 1, scan, content.size - (scan - content.ptr) - 1);
		/* insert '#' char into space we created */
		scan[1] = '#';
	}
	cl_git_rewritefile("renames/songof7cities.txt", content.ptr);

	check_single_patch_stats(
		g_repo, 1, 1, 1, 6, expected_sizes, expected);

	git_buf_dispose(&content);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_blame_options ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_4__ member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_2__ member_0; } ;
struct TYPE_14__ {int member_0; int member_2; char* member_5; int /*<<< orphan*/  lines_in_hunk; int /*<<< orphan*/  orig_path; int /*<<< orphan*/  final_start_line_number; int /*<<< orphan*/  member_6; TYPE_3__ member_4; int /*<<< orphan*/ * member_3; TYPE_1__ member_1; } ;
typedef  TYPE_5__ git_blame_hunk ;
struct TYPE_15__ {int /*<<< orphan*/  hunks; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BLAME_OPTIONS_INIT ; 
 TYPE_7__* g_blame ; 
 TYPE_5__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__strdup (int /*<<< orphan*/ ) ; 
 TYPE_7__* git_blame__alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,TYPE_5__*) ; 

void test_blame_getters__initialize(void)
{
	size_t i;
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;

	git_blame_hunk hunks[] = {
		{ 3, {{0}},  1, NULL, {{0}}, "a", 0},
		{ 3, {{0}},  4, NULL, {{0}}, "b", 0},
		{ 3, {{0}},  7, NULL, {{0}}, "c", 0},
		{ 3, {{0}}, 10, NULL, {{0}}, "d", 0},
		{ 3, {{0}}, 13, NULL, {{0}}, "e", 0},
	};

	g_blame = git_blame__alloc(NULL, opts, "");

	for (i=0; i<5; i++) {
		git_blame_hunk *h = git__calloc(1, sizeof(git_blame_hunk));
		h->final_start_line_number = hunks[i].final_start_line_number;
		h->orig_path = git__strdup(hunks[i].orig_path);
		h->lines_in_hunk = hunks[i].lines_in_hunk;

		git_vector_insert(&g_blame->hunks, h);
	}
}
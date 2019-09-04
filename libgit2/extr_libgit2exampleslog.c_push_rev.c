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
struct log_state {int hide; int /*<<< orphan*/  walker; int /*<<< orphan*/  sorting; int /*<<< orphan*/  repo; } ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_hide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_rev(struct log_state *s, git_object *obj, int hide)
{
	hide = s->hide ^ hide;

	/** Create revwalker on demand if it doesn't already exist. */
	if (!s->walker) {
		check_lg2(git_revwalk_new(&s->walker, s->repo),
			"Could not create revision walker", NULL);
		git_revwalk_sorting(s->walker, s->sorting);
	}

	if (!obj)
		check_lg2(git_revwalk_push_head(s->walker),
			"Could not find repository HEAD", NULL);
	else if (hide)
		check_lg2(git_revwalk_hide(s->walker, git_object_id(obj)),
			"Reference does not refer to a commit", NULL);
	else
		check_lg2(git_revwalk_push(s->walker, git_object_id(obj)),
			"Reference does not refer to a commit", NULL);

	git_object_free(obj);
}
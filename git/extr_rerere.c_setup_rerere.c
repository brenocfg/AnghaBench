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
struct string_list {int dummy; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 int RERERE_AUTOUPDATE ; 
 int RERERE_NOAUTOUPDATE ; 
 int RERERE_READONLY ; 
 int /*<<< orphan*/  git_path_merge_rr (struct repository*) ; 
 int /*<<< orphan*/  git_rerere_config () ; 
 int hold_lock_file_for_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_rerere_enabled () ; 
 int /*<<< orphan*/  read_rr (struct repository*,struct string_list*) ; 
 int rerere_autoupdate ; 
 int /*<<< orphan*/  write_lock ; 

int setup_rerere(struct repository *r, struct string_list *merge_rr, int flags)
{
	int fd;

	git_rerere_config();
	if (!is_rerere_enabled())
		return -1;

	if (flags & (RERERE_AUTOUPDATE|RERERE_NOAUTOUPDATE))
		rerere_autoupdate = !!(flags & RERERE_AUTOUPDATE);
	if (flags & RERERE_READONLY)
		fd = 0;
	else
		fd = hold_lock_file_for_update(&write_lock,
					       git_path_merge_rr(r),
					       LOCK_DIE_ON_ERROR);
	read_rr(r, merge_rr);
	return fd;
}
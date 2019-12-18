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
 struct string_list STRING_LIST_INIT_DUP ; 
 int do_plain_rerere (struct repository*,struct string_list*,int) ; 
 int /*<<< orphan*/  free_rerere_dirs () ; 
 int setup_rerere (struct repository*,struct string_list*,int) ; 

int repo_rerere(struct repository *r, int flags)
{
	struct string_list merge_rr = STRING_LIST_INIT_DUP;
	int fd, status;

	fd = setup_rerere(r, &merge_rr, flags);
	if (fd < 0)
		return 0;
	status = do_plain_rerere(r, &merge_rr, fd);
	free_rerere_dirs();
	return status;
}
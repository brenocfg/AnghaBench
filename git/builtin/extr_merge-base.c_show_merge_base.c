#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases_many_dirty (struct commit*,int,struct commit**) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int show_merge_base(struct commit **rev, int rev_nr, int show_all)
{
	struct commit_list *result, *r;

	result = get_merge_bases_many_dirty(rev[0], rev_nr - 1, rev + 1);

	if (!result)
		return 1;

	for (r = result; r; r = r->next) {
		printf("%s\n", oid_to_hex(&r->item->object.oid));
		if (!show_all)
			break;
	}

	free_commit_list(result);
	return 0;
}
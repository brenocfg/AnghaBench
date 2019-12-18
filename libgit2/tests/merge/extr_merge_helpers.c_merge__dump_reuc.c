#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* path; int* mode; int /*<<< orphan*/ * oid; } ;
typedef  TYPE_1__ git_index_reuc_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 size_t git_index_reuc_entrycount (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_reuc_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 char* git_oid_allocfmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void merge__dump_reuc(git_index *index)
{
	size_t i;
	const git_index_reuc_entry *reuc;

	printf ("\nREUC:\n");
	for (i = 0; i < git_index_reuc_entrycount(index); i++) {
		reuc = git_index_reuc_get_byindex(index, i);

		printf("%s ", reuc->path);
		printf("%o ", reuc->mode[0]);
		printf("%s\n", git_oid_allocfmt(&reuc->oid[0]));
		printf("          %o ", reuc->mode[1]);
		printf("          %s\n", git_oid_allocfmt(&reuc->oid[1]));
		printf("          %o ", reuc->mode[2]);
		printf("          %s ", git_oid_allocfmt(&reuc->oid[2]));
		printf("\n");
	}
	printf("\n");
}
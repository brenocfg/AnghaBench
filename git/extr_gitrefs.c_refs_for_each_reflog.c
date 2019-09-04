#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ref_store {TYPE_1__* be; } ;
struct ref_iterator {int dummy; } ;
struct do_for_each_ref_help {void* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  each_ref_fn ;
struct TYPE_2__ {struct ref_iterator* (* reflog_iterator_begin ) (struct ref_store*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  do_for_each_ref_helper ; 
 int do_for_each_repo_ref_iterator (int /*<<< orphan*/ ,struct ref_iterator*,int /*<<< orphan*/ ,struct do_for_each_ref_help*) ; 
 struct ref_iterator* stub1 (struct ref_store*) ; 
 int /*<<< orphan*/  the_repository ; 

int refs_for_each_reflog(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	struct ref_iterator *iter;
	struct do_for_each_ref_help hp = { fn, cb_data };

	iter = refs->be->reflog_iterator_begin(refs);

	return do_for_each_repo_ref_iterator(the_repository, iter,
					     do_for_each_ref_helper, &hp);
}
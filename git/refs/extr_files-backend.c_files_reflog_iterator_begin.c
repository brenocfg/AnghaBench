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
struct ref_store {int dummy; } ;
struct ref_iterator {int dummy; } ;
struct files_ref_store {int /*<<< orphan*/  gitcommondir; int /*<<< orphan*/  gitdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STORE_READ ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 struct ref_iterator* merge_ref_iterator_begin (int /*<<< orphan*/ ,struct ref_iterator*,struct ref_iterator*,int /*<<< orphan*/ ,struct files_ref_store*) ; 
 struct ref_iterator* reflog_iterator_begin (struct ref_store*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reflog_iterator_select ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ref_iterator *files_reflog_iterator_begin(struct ref_store *ref_store)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ,
			       "reflog_iterator_begin");

	if (!strcmp(refs->gitdir, refs->gitcommondir)) {
		return reflog_iterator_begin(ref_store, refs->gitcommondir);
	} else {
		return merge_ref_iterator_begin(
			0,
			reflog_iterator_begin(ref_store, refs->gitdir),
			reflog_iterator_begin(ref_store, refs->gitcommondir),
			reflog_iterator_select, refs);
	}
}
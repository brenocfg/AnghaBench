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
struct ref_cache {TYPE_1__* root; } ;
struct files_ref_store {struct ref_cache* loose; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_INCOMPLETE ; 
 int /*<<< orphan*/  add_entry_to_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_dir_entry (struct ref_cache*,char*,int,int) ; 
 struct ref_cache* create_ref_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ref_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  loose_fill_ref_dir ; 

__attribute__((used)) static struct ref_cache *get_loose_ref_cache(struct files_ref_store *refs)
{
	if (!refs->loose) {
		/*
		 * Mark the top-level directory complete because we
		 * are about to read the only subdirectory that can
		 * hold references:
		 */
		refs->loose = create_ref_cache(&refs->base, loose_fill_ref_dir);

		/* We're going to fill the top level ourselves: */
		refs->loose->root->flag &= ~REF_INCOMPLETE;

		/*
		 * Add an incomplete entry for "refs/" (to be filled
		 * lazily):
		 */
		add_entry_to_dir(get_ref_dir(refs->loose->root),
				 create_dir_entry(refs->loose, "refs/", 5, 1));
	}
	return refs->loose;
}
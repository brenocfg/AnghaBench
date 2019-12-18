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
struct split_index {int /*<<< orphan*/  saved_cache_nr; int /*<<< orphan*/  saved_cache; int /*<<< orphan*/ * replace_bitmap; int /*<<< orphan*/ * delete_bitmap; } ;
struct index_state {int /*<<< orphan*/  cache_nr; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ewah_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct split_index* init_split_index (struct index_state*) ; 

void finish_writing_split_index(struct index_state *istate)
{
	struct split_index *si = init_split_index(istate);

	ewah_free(si->delete_bitmap);
	ewah_free(si->replace_bitmap);
	si->delete_bitmap = NULL;
	si->replace_bitmap = NULL;
	free(istate->cache);
	istate->cache = si->saved_cache;
	istate->cache_nr = si->saved_cache_nr;
}
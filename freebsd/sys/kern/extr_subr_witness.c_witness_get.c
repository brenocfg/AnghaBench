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
struct witness {int w_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct witness* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct witness*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  w_free ; 
 int /*<<< orphan*/  w_free_cnt ; 
 int /*<<< orphan*/  w_list ; 
 int w_max_used_index ; 
 int /*<<< orphan*/  w_mtx ; 
 scalar_t__ witness_cold ; 
 int witness_count ; 
 int witness_watch ; 

__attribute__((used)) static struct witness *
witness_get(void)
{
	struct witness *w;
	int index;

	if (witness_cold == 0)
		mtx_assert(&w_mtx, MA_OWNED);

	if (witness_watch == -1) {
		mtx_unlock_spin(&w_mtx);
		return (NULL);
	}
	if (STAILQ_EMPTY(&w_free)) {
		witness_watch = -1;
		mtx_unlock_spin(&w_mtx);
		printf("WITNESS: unable to allocate a new witness object\n");
		return (NULL);
	}
	w = STAILQ_FIRST(&w_free);
	STAILQ_REMOVE_HEAD(&w_free, w_list);
	w_free_cnt--;
	index = w->w_index;
	MPASS(index > 0 && index == w_max_used_index+1 &&
	    index < witness_count);
	bzero(w, sizeof(*w));
	w->w_index = index;
	if (index > w_max_used_index)
		w_max_used_index = index;
	return (w);
}
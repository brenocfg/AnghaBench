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
struct sf_buf {scalar_t__ ref_count; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct sf_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_HAS_DMAP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sf_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_entry ; 
 int /*<<< orphan*/  list_entry ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsfbufsused ; 
 scalar_t__ sf_buf_alloc_want ; 
 int /*<<< orphan*/  sf_buf_freelist ; 
 int /*<<< orphan*/  sf_buf_lock ; 
 scalar_t__ sf_buf_unmap (struct sf_buf*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
sf_buf_free(struct sf_buf *sf)
{

	if (PMAP_HAS_DMAP)
		return;

	mtx_lock(&sf_buf_lock);
	sf->ref_count--;
	if (sf->ref_count == 0) {
		TAILQ_INSERT_TAIL(&sf_buf_freelist, sf, free_entry);
		nsfbufsused--;
		if (sf_buf_unmap(sf)) {
			sf->m = NULL;
			LIST_REMOVE(sf, list_entry);
		}
		if (sf_buf_alloc_want > 0)
			wakeup(&sf_buf_freelist);
	}
	mtx_unlock(&sf_buf_lock);
}
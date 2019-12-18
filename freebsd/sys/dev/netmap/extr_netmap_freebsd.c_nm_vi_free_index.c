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
typedef  int uint8_t ;
struct TYPE_2__ {int active; int* index; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_prerr (char*,int) ; 
 TYPE_1__ nm_vi_indices ; 

__attribute__((used)) static void
nm_vi_free_index(uint8_t val)
{
	int i, lim;

	mtx_lock(&nm_vi_indices.lock);
	lim = nm_vi_indices.active;
	for (i = 0; i < lim; i++) {
		if (nm_vi_indices.index[i] == val) {
			/* swap index[lim-1] and j */
			int tmp = nm_vi_indices.index[lim-1];
			nm_vi_indices.index[lim-1] = val;
			nm_vi_indices.index[i] = tmp;
			nm_vi_indices.active--;
			break;
		}
	}
	if (lim == nm_vi_indices.active)
		nm_prerr("Index %u not found", val);
	mtx_unlock(&nm_vi_indices.lock);
}
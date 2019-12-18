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
struct TYPE_2__ {scalar_t__ active; int* index; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ NM_VI_MAX ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ nm_vi_indices ; 

__attribute__((used)) static int
nm_vi_get_index(void)
{
	int ret;

	mtx_lock(&nm_vi_indices.lock);
	ret = nm_vi_indices.active == NM_VI_MAX ? -1 :
		nm_vi_indices.index[nm_vi_indices.active++];
	mtx_unlock(&nm_vi_indices.lock);
	return ret;
}
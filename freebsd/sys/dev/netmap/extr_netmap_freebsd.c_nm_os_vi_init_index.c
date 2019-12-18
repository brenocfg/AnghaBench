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
struct TYPE_2__ {int* index; int /*<<< orphan*/  lock; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int NM_VI_MAX ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ nm_vi_indices ; 

void
nm_os_vi_init_index(void)
{
	int i;
	for (i = 0; i < NM_VI_MAX; i++)
		nm_vi_indices.index[i] = i;
	nm_vi_indices.active = 0;
	mtx_init(&nm_vi_indices.lock, "nm_vi_indices_lock", NULL, MTX_DEF);
}
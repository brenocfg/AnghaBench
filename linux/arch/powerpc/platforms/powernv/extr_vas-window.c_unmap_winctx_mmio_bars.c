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
typedef  int /*<<< orphan*/  u64 ;
struct vas_window {int /*<<< orphan*/ * uwc_map; int /*<<< orphan*/ * hvwc_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_hvwc_mmio_bar (struct vas_window*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_uwc_mmio_bar (struct vas_window*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_region (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vas_mutex ; 

__attribute__((used)) static void unmap_winctx_mmio_bars(struct vas_window *window)
{
	int len;
	void *uwc_map;
	void *hvwc_map;
	u64 busaddr_start;

	mutex_lock(&vas_mutex);

	hvwc_map = window->hvwc_map;
	window->hvwc_map = NULL;

	uwc_map = window->uwc_map;
	window->uwc_map = NULL;

	mutex_unlock(&vas_mutex);

	if (hvwc_map) {
		get_hvwc_mmio_bar(window, &busaddr_start, &len);
		unmap_region(hvwc_map, busaddr_start, len);
	}

	if (uwc_map) {
		get_uwc_mmio_bar(window, &busaddr_start, &len);
		unmap_region(uwc_map, busaddr_start, len);
	}
}
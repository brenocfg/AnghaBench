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
struct vas_window {int winid; struct vas_instance* vinst; } ;
struct vas_instance {int /*<<< orphan*/  ida; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vas_window* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct vas_window*) ; 
 struct vas_window* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ map_winctx_mmio_bars (struct vas_window*) ; 
 int vas_assign_window_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vas_release_window_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vas_window_init_dbgdir (struct vas_window*) ; 

__attribute__((used)) static struct vas_window *vas_window_alloc(struct vas_instance *vinst)
{
	int winid;
	struct vas_window *window;

	winid = vas_assign_window_id(&vinst->ida);
	if (winid < 0)
		return ERR_PTR(winid);

	window = kzalloc(sizeof(*window), GFP_KERNEL);
	if (!window)
		goto out_free;

	window->vinst = vinst;
	window->winid = winid;

	if (map_winctx_mmio_bars(window))
		goto out_free;

	vas_window_init_dbgdir(window);

	return window;

out_free:
	kfree(window);
	vas_release_window_id(&vinst->ida, winid);
	return ERR_PTR(-ENOMEM);
}
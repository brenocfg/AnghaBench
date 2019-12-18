#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {unsigned long driver_pages; unsigned long hard_limit; scalar_t__ balloon_high; scalar_t__ balloon_low; int /*<<< orphan*/  current_pages; int /*<<< orphan*/  target_pages; } ;
struct TYPE_4__ {int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  balloon_mutex ; 
 int /*<<< orphan*/  balloon_process ; 
 TYPE_3__ bs ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realmem ; 
 TYPE_1__ target_watch ; 
 int /*<<< orphan*/  watch_target ; 
 int xs_register_watch (TYPE_1__*) ; 

__attribute__((used)) static int
xenballoon_attach(device_t dev)
{
	int err;

	mtx_init(&balloon_mutex, "balloon_mutex", NULL, MTX_DEF);

	bs.current_pages = realmem;
	bs.target_pages  = bs.current_pages;
	bs.balloon_low   = 0;
	bs.balloon_high  = 0;
	bs.driver_pages  = 0UL;
	bs.hard_limit    = ~0UL;

	kproc_create(balloon_process, NULL, NULL, 0, 0, "balloon");
    
	target_watch.callback = watch_target;

	err = xs_register_watch(&target_watch);
	if (err)
		device_printf(dev,
		    "xenballon: failed to set balloon watcher\n");

	return (err);
}
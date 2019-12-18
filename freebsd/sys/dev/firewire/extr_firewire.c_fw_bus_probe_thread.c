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
struct firewire_comm {scalar_t__ status; int /*<<< orphan*/  wait_lock; } ;

/* Variables and functions */
 scalar_t__ FWBUSDETACH ; 
 scalar_t__ FWBUSEXPDONE ; 
 scalar_t__ FWBUSEXPLORE ; 
 int PCATCH ; 
 int PWAIT ; 
 scalar_t__ firewire_debug ; 
 int /*<<< orphan*/  fw_attach_dev (struct firewire_comm*) ; 
 int /*<<< orphan*/  fw_explore (struct firewire_comm*) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (void*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
fw_bus_probe_thread(void *arg)
{
	struct firewire_comm *fc;

	fc = arg;

	mtx_lock(&fc->wait_lock);
	while (fc->status != FWBUSDETACH) {
		if (fc->status == FWBUSEXPLORE) {
			mtx_unlock(&fc->wait_lock);
			fw_explore(fc);
			fc->status = FWBUSEXPDONE;
			if (firewire_debug)
				printf("bus_explore done\n");
			fw_attach_dev(fc);
			mtx_lock(&fc->wait_lock);
		}
		msleep((void *)fc, &fc->wait_lock, PWAIT|PCATCH, "-", 0);
	}
	mtx_unlock(&fc->wait_lock);
	kproc_exit(0);
}
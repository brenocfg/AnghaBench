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
struct TYPE_2__ {int shutdown_requested; int /*<<< orphan*/  startup_sync_barrier; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_barrier_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_all_threads () ; 

__attribute__((used)) static void on_sigterm(int signo)
{
    conf.shutdown_requested = 1;
    if (!h2o_barrier_done(&conf.startup_sync_barrier)) {
        /* initialization hasn't completed yet, exit right away */
        exit(0);
    }
    notify_all_threads();
}
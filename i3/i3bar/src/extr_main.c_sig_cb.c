#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ev_loop {int dummy; } ;
struct TYPE_3__ {int signum; } ;
typedef  TYPE_1__ ev_signal ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  EVUNLOOP_ALL ; 
#define  SIGHUP 130 
#define  SIGINT 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  ev_unloop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_loop ; 

__attribute__((used)) static void sig_cb(struct ev_loop *loop, ev_signal *watcher, int revents) {
    switch (watcher->signum) {
        case SIGTERM:
            DLOG("Got a SIGTERM, stopping\n");
            break;
        case SIGINT:
            DLOG("Got a SIGINT, stopping\n");
            break;
        case SIGHUP:
            DLOG("Got a SIGHUP, stopping\n");
    }
    ev_unloop(main_loop, EVUNLOOP_ALL);
}
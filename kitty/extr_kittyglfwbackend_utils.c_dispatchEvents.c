#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int revents; } ;
typedef  scalar_t__ nfds_t ;
struct TYPE_4__ {int events; int ready; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  fd; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Watch ;
struct TYPE_5__ {scalar_t__ watches_count; struct pollfd* fds; TYPE_1__* watches; } ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dispatchEvents(EventLoopData *eld) {
    for (nfds_t i = 0; i < eld->watches_count; i++) {
        Watch *ww = eld->watches + i;
        struct pollfd *pfd = eld->fds + i;
        if (pfd->revents & ww->events) {
            ww->ready = 1;
            if (ww->callback) ww->callback(ww->fd, pfd->revents, ww->callback_data);
        } else ww->ready = 0;
    }
}
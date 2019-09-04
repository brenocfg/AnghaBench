#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nfds_t ;
struct TYPE_6__ {int /*<<< orphan*/  events; scalar_t__ enabled; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ Watch ;
struct TYPE_7__ {scalar_t__ watches_count; TYPE_1__* fds; TYPE_2__* watches; } ;
struct TYPE_5__ {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ EventLoopData ;

/* Variables and functions */

void
update_fds(EventLoopData *eld) {
    for (nfds_t i = 0; i < eld->watches_count; i++) {
        Watch *w = eld->watches + i;
        eld->fds[i].fd = w->fd;
        eld->fds[i].events = w->enabled ? w->events : 0;
    }
}
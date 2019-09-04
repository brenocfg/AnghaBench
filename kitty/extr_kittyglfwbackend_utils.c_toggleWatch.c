#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t nfds_t ;
typedef  scalar_t__ id_type ;
struct TYPE_6__ {size_t watches_count; TYPE_1__* watches; } ;
struct TYPE_5__ {scalar_t__ id; int enabled; } ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 int /*<<< orphan*/  update_fds (TYPE_2__*) ; 

void
toggleWatch(EventLoopData *eld, id_type watch_id, int enabled) {
    for (nfds_t i = 0; i < eld->watches_count; i++) {
        if (eld->watches[i].id == watch_id) {
            if (eld->watches[i].enabled != enabled) {
                eld->watches[i].enabled = enabled;
                update_fds(eld);
            }
            break;
        }
    }
}
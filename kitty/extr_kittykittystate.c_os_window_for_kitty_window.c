#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ id_type ;
struct TYPE_7__ {size_t num_windows; TYPE_1__* windows; } ;
typedef  TYPE_2__ Tab ;
struct TYPE_9__ {size_t num_os_windows; TYPE_3__* os_windows; } ;
struct TYPE_8__ {size_t num_tabs; TYPE_2__* tabs; } ;
struct TYPE_6__ {scalar_t__ id; } ;
typedef  TYPE_3__ OSWindow ;

/* Variables and functions */
 TYPE_5__ global_state ; 

OSWindow*
os_window_for_kitty_window(id_type kitty_window_id) {
    for (size_t i = 0; i < global_state.num_os_windows; i++) {
        OSWindow *w = global_state.os_windows + i;
        for (size_t t = 0; t < w->num_tabs; t++) {
            Tab *tab = w->tabs + t;
            for (size_t c = 0; c < tab->num_windows; c++) {
                if (tab->windows[c].id == kitty_window_id) return w;
            }
        }
    }
    return NULL;
}
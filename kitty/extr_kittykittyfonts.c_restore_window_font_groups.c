#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {size_t num_os_windows; TYPE_1__* os_windows; } ;
struct TYPE_4__ {scalar_t__ temp_font_group_id; int /*<<< orphan*/ * fonts_data; } ;
typedef  TYPE_1__ OSWindow ;
typedef  int /*<<< orphan*/ * FONTS_DATA_HANDLE ;

/* Variables and functions */
 TYPE_3__* font_groups ; 
 TYPE_2__ global_state ; 
 size_t num_font_groups ; 

__attribute__((used)) static inline void
restore_window_font_groups() {
    for (size_t o = 0; o < global_state.num_os_windows; o++) {
        OSWindow *w = global_state.os_windows + o;
        w->fonts_data = NULL;
        for (size_t i = 0; i < num_font_groups; i++) {
            if (font_groups[i].id == w->temp_font_group_id) {
                w->fonts_data = (FONTS_DATA_HANDLE)(font_groups + i);
                break;
            }
        }
    }
}
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
struct TYPE_7__ {size_t num_os_windows; TYPE_1__* os_windows; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {scalar_t__ temp_font_group_id; } ;
typedef  TYPE_1__ OSWindow ;
typedef  TYPE_2__ FontGroup ;

/* Variables and functions */
 TYPE_3__ global_state ; 

__attribute__((used)) static inline bool
font_group_is_unused(FontGroup *fg) {
    for (size_t o = 0; o < global_state.num_os_windows; o++) {
        OSWindow *w = global_state.os_windows + o;
        if (w->temp_font_group_id == fg->id) return false;
    }
    return true;
}
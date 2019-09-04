#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* rect_buf; int /*<<< orphan*/  vao_idx; } ;
struct TYPE_7__ {size_t num_windows; TYPE_4__* windows; TYPE_1__ border_rects; } ;
typedef  TYPE_2__ Tab ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  remove_vao (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_window_inner (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
destroy_tab(Tab *tab) {
    for (size_t i = tab->num_windows; i > 0; i--) remove_window_inner(tab, tab->windows[i - 1].id);
    remove_vao(tab->border_rects.vao_idx);
    free(tab->border_rects.rect_buf); tab->border_rects.rect_buf = NULL;
    free(tab->windows); tab->windows = NULL;
}
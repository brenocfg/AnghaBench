#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ Tab ;
struct TYPE_7__ {int /*<<< orphan*/  vao_idx; int /*<<< orphan*/  screen; } ;
struct TYPE_9__ {size_t num_tabs; TYPE_2__* tabs; int /*<<< orphan*/  gvao_idx; TYPE_1__ tab_bar_render_data; scalar_t__ offscreen_texture_id; int /*<<< orphan*/  window_title; } ;
typedef  TYPE_3__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  free_texture (scalar_t__*) ; 
 int /*<<< orphan*/  remove_tab_inner (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_vao (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
destroy_os_window_item(OSWindow *w) {
    for (size_t t = w->num_tabs; t > 0; t--) {
        Tab *tab = w->tabs + t - 1;
        remove_tab_inner(w, tab->id);
    }
    Py_CLEAR(w->window_title); Py_CLEAR(w->tab_bar_render_data.screen);
    if (w->offscreen_texture_id) free_texture(&w->offscreen_texture_id);
    remove_vao(w->tab_bar_render_data.vao_idx);
    remove_vao(w->gvao_idx);
    free(w->tabs); w->tabs = NULL;
}
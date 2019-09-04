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
struct TYPE_4__ {int /*<<< orphan*/  gvao_idx; int /*<<< orphan*/  vao_idx; int /*<<< orphan*/  screen; } ;
struct TYPE_5__ {TYPE_1__ render_data; int /*<<< orphan*/  title; } ;
typedef  TYPE_2__ Window ;

/* Variables and functions */
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_vao (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
destroy_window(Window *w) {
    Py_CLEAR(w->render_data.screen); Py_CLEAR(w->title);
    remove_vao(w->render_data.vao_idx); remove_vao(w->render_data.gvao_idx);
}
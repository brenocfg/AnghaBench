#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ groups_capacity; int /*<<< orphan*/ * groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  box_drawing_function ; 
 int /*<<< orphan*/  clear_symbol_maps () ; 
 int /*<<< orphan*/  descriptor_for_idx ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_font_groups () ; 
 TYPE_1__ group_state ; 
 int /*<<< orphan*/ * harfbuzz_buffer ; 
 int /*<<< orphan*/  hb_buffer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prerender_function ; 
 int /*<<< orphan*/  python_send_to_gpu_impl ; 

__attribute__((used)) static void
finalize(void) {
    Py_CLEAR(python_send_to_gpu_impl);
    clear_symbol_maps();
    Py_CLEAR(box_drawing_function);
    Py_CLEAR(prerender_function);
    Py_CLEAR(descriptor_for_idx);
    free_font_groups();
    if (harfbuzz_buffer) { hb_buffer_destroy(harfbuzz_buffer); harfbuzz_buffer = NULL; }
    free(group_state.groups); group_state.groups = NULL; group_state.groups_capacity = 0;
}
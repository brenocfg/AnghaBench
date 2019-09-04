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
typedef  int index_type ;
typedef  int attrs_type ;
struct TYPE_6__ {scalar_t__* cc_idx; scalar_t__ ch; } ;
struct TYPE_5__ {int attrs; } ;
typedef  TYPE_1__ GPUCell ;
typedef  TYPE_2__ CPUCell ;

/* Variables and functions */
 int WIDTH_MASK ; 
 unsigned int arraysz (scalar_t__*) ; 
 scalar_t__ codepoint_for_mark (scalar_t__) ; 
 int /*<<< orphan*/  harfbuzz_buffer ; 
 int /*<<< orphan*/  hb_buffer_add_utf32 (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_buffer_clear_contents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_guess_segment_properties (int /*<<< orphan*/ ) ; 
 scalar_t__* shape_buffer ; 

__attribute__((used)) static inline void
load_hb_buffer(CPUCell *first_cpu_cell, GPUCell *first_gpu_cell, index_type num_cells) {
    index_type num;
    hb_buffer_clear_contents(harfbuzz_buffer);
    while (num_cells) {
        attrs_type prev_width = 0;
        for (num = 0; num_cells && num < arraysz(shape_buffer) - 20 - arraysz(first_cpu_cell->cc_idx); first_cpu_cell++, first_gpu_cell++, num_cells--) {
            if (prev_width == 2) { prev_width = 0; continue; }
            shape_buffer[num++] = first_cpu_cell->ch;
            prev_width = first_gpu_cell->attrs & WIDTH_MASK;
            for (unsigned i = 0; i < arraysz(first_cpu_cell->cc_idx) && first_cpu_cell->cc_idx[i]; i++) {
                shape_buffer[num++] = codepoint_for_mark(first_cpu_cell->cc_idx[i]);
            }
        }
        hb_buffer_add_utf32(harfbuzz_buffer, shape_buffer, num, 0, num);
    }
    hb_buffer_guess_segment_properties(harfbuzz_buffer);
}
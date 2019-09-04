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
typedef  unsigned int attrs_type ;
struct TYPE_9__ {int /*<<< orphan*/ * cc_idx; scalar_t__ ch; } ;
struct TYPE_8__ {int codepoints_consumed; int num_codepoints; TYPE_3__* cpu_cell; scalar_t__ current_codepoint; TYPE_1__* gpu_cell; } ;
struct TYPE_7__ {unsigned int attrs; } ;
typedef  TYPE_2__ CellData ;
typedef  TYPE_3__ CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int,unsigned int) ; 
 unsigned int WIDTH_MASK ; 
 scalar_t__ codepoint_for_mark (int /*<<< orphan*/ ) ; 
 int num_codepoints_in_cell (TYPE_3__*) ; 

__attribute__((used)) static inline unsigned int
check_cell_consumed(CellData *cell_data, CPUCell *last_cpu_cell) {
    cell_data->codepoints_consumed++;
    if (cell_data->codepoints_consumed >= cell_data->num_codepoints) {
        attrs_type width = cell_data->gpu_cell->attrs & WIDTH_MASK;
        cell_data->cpu_cell += MAX(1, width);
        cell_data->gpu_cell += MAX(1, width);
        cell_data->codepoints_consumed = 0;
        if (cell_data->cpu_cell <= last_cpu_cell) {
            cell_data->num_codepoints = num_codepoints_in_cell(cell_data->cpu_cell);
            cell_data->current_codepoint = cell_data->cpu_cell->ch;
        } else cell_data->current_codepoint = 0;
        return width;
    } else {
        switch(cell_data->codepoints_consumed) {
            case 0:
                cell_data->current_codepoint = cell_data->cpu_cell->ch;
                break;
            default:
                cell_data->current_codepoint = codepoint_for_mark(cell_data->cpu_cell->cc_idx[cell_data->codepoints_consumed - 1]);
                break;
        }
    }
    return 0;
}
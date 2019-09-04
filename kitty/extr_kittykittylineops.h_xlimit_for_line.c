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
typedef  int index_type ;
struct TYPE_7__ {int xnum; TYPE_2__* gpu_cells; TYPE_1__* cpu_cells; } ;
struct TYPE_6__ {int attrs; } ;
struct TYPE_5__ {scalar_t__ ch; } ;
typedef  TYPE_3__ Line ;

/* Variables and functions */
 scalar_t__ BLANK_CHAR ; 
 int WIDTH_MASK ; 

__attribute__((used)) static inline index_type
xlimit_for_line(Line *line) {
    index_type xlimit = line->xnum;
    if (BLANK_CHAR == 0) {
        while (xlimit > 0 && (line->cpu_cells[xlimit - 1].ch) == BLANK_CHAR) xlimit--;
        if (xlimit < line->xnum && (line->gpu_cells[xlimit > 0 ? xlimit - 1 : xlimit].attrs & WIDTH_MASK) == 2) xlimit++;
    }
    return xlimit;
}
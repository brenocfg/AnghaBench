#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int xnum; int needs_free; int /*<<< orphan*/ * gpu_cells; int /*<<< orphan*/ * cpu_cells; } ;
typedef  TYPE_1__ Line ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 scalar_t__ BLANK_CHAR ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 void* PyMem_Calloc (int,int) ; 
 void* PyMem_Malloc (int) ; 
 int /*<<< orphan*/  clear_chars_in_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static inline bool
allocate_line_storage(Line *line, bool initialize) {
    if (initialize) {
        line->cpu_cells = PyMem_Calloc(line->xnum, sizeof(CPUCell));
        line->gpu_cells = PyMem_Calloc(line->xnum, sizeof(GPUCell));
        if (line->cpu_cells == NULL || line->gpu_cells) { PyErr_NoMemory(); return false; }
        if (BLANK_CHAR != 0) clear_chars_in_line(line->cpu_cells, line->gpu_cells, line->xnum, BLANK_CHAR);
    } else {
        line->cpu_cells = PyMem_Malloc(line->xnum * sizeof(CPUCell));
        line->gpu_cells = PyMem_Malloc(line->xnum * sizeof(GPUCell));
        if (line->cpu_cells == NULL || line->gpu_cells == NULL) { PyErr_NoMemory(); return false; }
    }
    line->needs_free = 1;
    return true;
}
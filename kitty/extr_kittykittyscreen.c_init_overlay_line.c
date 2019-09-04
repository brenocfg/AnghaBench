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
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_4__ {int is_active; scalar_t__ xstart; scalar_t__ ynum; scalar_t__ xnum; void* gpu_cells; void* cpu_cells; } ;
struct TYPE_5__ {TYPE_1__ overlay_line; } ;
typedef  TYPE_2__ Screen ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 void* PyMem_Calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyMem_Free (void*) ; 

__attribute__((used)) static inline bool
init_overlay_line(Screen *self, index_type columns) {
    PyMem_Free(self->overlay_line.cpu_cells);
    PyMem_Free(self->overlay_line.gpu_cells);
    self->overlay_line.cpu_cells = PyMem_Calloc(columns, sizeof(CPUCell));
    self->overlay_line.gpu_cells = PyMem_Calloc(columns, sizeof(GPUCell));
    if (!self->overlay_line.cpu_cells || !self->overlay_line.gpu_cells) {
        PyErr_NoMemory(); return false;
    }
    self->overlay_line.is_active = false;
    self->overlay_line.xnum = 0;
    self->overlay_line.ynum = 0;
    self->overlay_line.xstart = 0;
    return true;
}
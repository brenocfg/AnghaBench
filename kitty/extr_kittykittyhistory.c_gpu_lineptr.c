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
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_3__ {int /*<<< orphan*/  xnum; } ;
typedef  TYPE_1__ HistoryBuf ;
typedef  int /*<<< orphan*/  GPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  gpu_cells ; 
 int /*<<< orphan*/  seg_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline GPUCell*
gpu_lineptr(HistoryBuf *self, index_type y) {
    seg_ptr(gpu_cells, self->xnum);
}
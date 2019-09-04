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
struct TYPE_3__ {int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; } ;
typedef  int /*<<< orphan*/  LineBuf ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_lineptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_lineptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
init_line(LineBuf *lb, Line *l, index_type ynum) {
    l->cpu_cells = cpu_lineptr(lb, ynum);
    l->gpu_cells = gpu_lineptr(lb, ynum);
}
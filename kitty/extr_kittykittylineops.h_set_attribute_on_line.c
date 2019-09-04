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
typedef  int uint32_t ;
typedef  size_t index_type ;
typedef  int attrs_type ;
struct TYPE_3__ {int attrs; } ;
typedef  TYPE_1__ GPUCell ;

/* Variables and functions */
 int DECORATION_SHIFT ; 

__attribute__((used)) static inline void
set_attribute_on_line(GPUCell *cells, uint32_t shift, uint32_t val, index_type xnum) {
    // Set a single attribute on all cells in the line
    attrs_type mask = shift == DECORATION_SHIFT ? 3 : 1;
    attrs_type aval = (val & mask) << shift;
    mask = ~(mask << shift);
    for (index_type i = 0; i < xnum; i++) cells[i].attrs = (cells[i].attrs & mask) | aval;
}
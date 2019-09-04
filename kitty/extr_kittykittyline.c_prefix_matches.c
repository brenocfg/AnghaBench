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
typedef  size_t index_type ;
struct TYPE_5__ {size_t xnum; TYPE_1__* cpu_cells; } ;
struct TYPE_4__ {unsigned char ch; } ;
typedef  TYPE_2__ Line ;

/* Variables and functions */

__attribute__((used)) static inline bool
prefix_matches(Line *self, index_type at, const char* prefix, index_type prefix_len) {
    if (prefix_len > at) return false;
    index_type p, i;
    for (p = at - prefix_len, i = 0; i < prefix_len && p < self->xnum; i++, p++) {
        if ((self->cpu_cells[p].ch) != (unsigned char)prefix[i]) return false;
    }
    return i == prefix_len;
}
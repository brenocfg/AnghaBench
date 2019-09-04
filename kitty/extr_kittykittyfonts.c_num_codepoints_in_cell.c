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
struct TYPE_3__ {scalar_t__* cc_idx; } ;
typedef  TYPE_1__ CPUCell ;

/* Variables and functions */
 unsigned int arraysz (scalar_t__*) ; 

__attribute__((used)) static inline unsigned int
num_codepoints_in_cell(CPUCell *cell) {
    unsigned int ans = 1;
    for (unsigned i = 0; i < arraysz(cell->cc_idx) && cell->cc_idx[i]; i++) ans++;
    return ans;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int index_type ;

/* Variables and functions */

__attribute__((used)) static inline void
init_tabstops(bool *tabstops, index_type count) {
    // In terminfo we specify the number of initial tabstops (it) as 8
    for (unsigned int t=0; t < count; t++) {
        tabstops[t] = t % 8 == 0 ? true : false;
    }
}
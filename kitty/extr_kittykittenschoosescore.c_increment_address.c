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
typedef  size_t len_t ;
struct TYPE_3__ {size_t needle_len; scalar_t__* address; scalar_t__* positions_count; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */

__attribute__((used)) static inline bool
increment_address(WorkSpace *w) {
    len_t pos = w->needle_len - 1;
    while(true) {
        w->address[pos]++;
        if (w->address[pos] < w->positions_count[pos]) return true;
        if (pos == 0) break;
        w->address[pos--] = 0;
    }
    return false;
}
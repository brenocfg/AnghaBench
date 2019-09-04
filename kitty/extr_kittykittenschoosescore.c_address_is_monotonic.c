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
typedef  scalar_t__ len_t ;
struct TYPE_3__ {scalar_t__ needle_len; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */
 scalar_t__ POSITION (scalar_t__) ; 

__attribute__((used)) static inline bool
address_is_monotonic(WorkSpace *w) {
    // Check if the character positions pointed to by the current address are monotonic
    for (len_t i = 1; i < w->needle_len; i++) {
        if (POSITION(i) <= POSITION(i-1)) return false;
    }
    return true;
}
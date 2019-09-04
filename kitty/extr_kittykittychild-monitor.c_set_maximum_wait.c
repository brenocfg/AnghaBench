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

/* Variables and functions */
 double maximum_wait ; 

__attribute__((used)) static inline void
set_maximum_wait(double val) {
    if (val >= 0 && (val < maximum_wait || maximum_wait < 0)) maximum_wait = val;
}
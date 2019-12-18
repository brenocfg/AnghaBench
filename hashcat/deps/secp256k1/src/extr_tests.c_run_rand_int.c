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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  ms ;

/* Variables and functions */
 int /*<<< orphan*/  test_rand_int (int const,int const) ; 

void run_rand_int(void) {
    static const uint32_t ms[] = {1, 3, 17, 1000, 13771, 999999, 33554432};
    static const uint32_t ss[] = {1, 3, 6, 9, 13, 31, 64};
    unsigned int m, s;
    for (m = 0; m < sizeof(ms) / sizeof(ms[0]); m++) {
        for (s = 0; s < sizeof(ss) / sizeof(ss[0]); s++) {
            test_rand_int(ms[m] * ss[s], ss[s]);
        }
    }
}
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
 int count ; 
 int /*<<< orphan*/  test_ec_combine () ; 

void run_ec_combine(void) {
    int i;
    for (i = 0; i < count * 8; i++) {
         test_ec_combine();
    }
}
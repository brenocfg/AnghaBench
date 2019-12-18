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
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int count ; 
 int /*<<< orphan*/  random_fe_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_group_decompress (int /*<<< orphan*/ *) ; 

void run_group_decompress(void) {
    int i;
    for (i = 0; i < count * 4; i++) {
        secp256k1_fe fe;
        random_fe_test(&fe);
        test_group_decompress(&fe);
    }
}
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
 int /*<<< orphan*/  cond_true ; 
 int /*<<< orphan*/  init_cond_rand (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  loss_cond_down ; 
 int /*<<< orphan*/  loss_cond_up ; 
 int /*<<< orphan*/  loss_core ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_downstream(void)
{
    size_t i;

    loss_cond_up = cond_true;

    for (i = 0; i != 100; ++i) {
        init_cond_rand(&loss_cond_down, 3, 4);
        subtest("75%", loss_core);

        init_cond_rand(&loss_cond_down, 1, 2);
        subtest("50%", loss_core);

        init_cond_rand(&loss_cond_down, 1, 4);
        subtest("25%", loss_core);

        init_cond_rand(&loss_cond_down, 1, 10);
        subtest("10%", loss_core);

        init_cond_rand(&loss_cond_down, 1, 20);
        subtest("5%", loss_core);

        init_cond_rand(&loss_cond_down, 1, 40);
        subtest("2.5%", loss_core);

        init_cond_rand(&loss_cond_down, 1, 64);
        subtest("1.6%", loss_core);
    }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_tests; int failed; } ;

/* Variables and functions */
 TYPE_1__* cur_tests ; 
 int /*<<< orphan*/  indent () ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int done_testing(void)
{
    indent();
    printf("1..%d\n", cur_tests->num_tests);
    return cur_tests->failed;
}
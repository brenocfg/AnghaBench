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
typedef  int /*<<< orphan*/  JobData ;

/* Variables and functions */
 int /*<<< orphan*/  run_scoring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void*
run_scoring_pthreads(void *job_data) {
    run_scoring((JobData*)job_data);
    return NULL;
}
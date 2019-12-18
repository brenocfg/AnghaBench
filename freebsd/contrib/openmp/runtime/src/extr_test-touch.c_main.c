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
 int /*<<< orphan*/  omp_get_max_threads () ; 
 int /*<<< orphan*/  omp_get_num_threads () ; 
 int /*<<< orphan*/  omp_get_wtime () ; 

int main() {
    omp_get_wtime();
    omp_get_num_threads();
    omp_get_max_threads();
    return 0;
}
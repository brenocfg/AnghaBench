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
 char* get_freqs (unsigned long long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  result_as_status_result ; 

char *get_status_results_freqs (unsigned long long volume_id, int transaction_id) {
  return get_freqs (volume_id, transaction_id, result_as_status_result);
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct sa_query_result {int /*<<< orphan*/ * p_result_madw; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int umad_size () ; 

void sa_free_result_mad(struct sa_query_result *result)
{
	if (result->p_result_madw) {
		free((uint8_t *) result->p_result_madw - umad_size());
		result->p_result_madw = NULL;
	}
}
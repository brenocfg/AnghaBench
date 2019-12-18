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
 int /*<<< orphan*/  V_counter_zone ; 
 int /*<<< orphan*/  atomic_subtract_int (unsigned int*,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,unsigned int*) ; 

void
tcp_fastopen_decrement_counter(unsigned int *counter)
{
	if (*counter == 1)
		uma_zfree(V_counter_zone, counter);
	else
		atomic_subtract_int(counter, 1);
}
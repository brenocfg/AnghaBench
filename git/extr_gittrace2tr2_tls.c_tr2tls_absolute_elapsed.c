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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  tr2tls_thread_main ; 
 scalar_t__ tr2tls_us_start_main ; 

uint64_t tr2tls_absolute_elapsed(uint64_t us)
{
	if (!tr2tls_thread_main)
		return 0;

	return us - tr2tls_us_start_main;
}
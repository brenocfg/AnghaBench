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
 int /*<<< orphan*/  louis ; 
 int /*<<< orphan*/  v7_exit_coherency_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dcscb_cpu_cache_disable(void)
{
	/* Disable and flush the local CPU cache. */
	v7_exit_coherency_flush(louis);
}
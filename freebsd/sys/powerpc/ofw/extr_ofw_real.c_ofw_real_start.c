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
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_bounce_mtx ; 
 scalar_t__ of_bounce_offset ; 

__attribute__((used)) static void
ofw_real_start(void)
{
	mtx_lock(&of_bounce_mtx);
	of_bounce_offset = 0;
}
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
typedef  int /*<<< orphan*/  ibnd_node_t ;

/* Variables and functions */
 scalar_t__ is_line (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spine (int /*<<< orphan*/ *) ; 

int is_chassis_switch(ibnd_node_t * n)
{
	return (is_spine(n) || is_line(n));
}
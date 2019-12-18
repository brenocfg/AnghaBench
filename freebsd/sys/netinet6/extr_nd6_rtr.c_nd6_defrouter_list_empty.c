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
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_nd6_defrouter ; 

bool
nd6_defrouter_list_empty(void)
{

	return (TAILQ_EMPTY(&V_nd6_defrouter));
}
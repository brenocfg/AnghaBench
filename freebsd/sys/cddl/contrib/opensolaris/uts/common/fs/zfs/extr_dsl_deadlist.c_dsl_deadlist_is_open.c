#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * dl_os; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */

boolean_t
dsl_deadlist_is_open(dsl_deadlist_t *dl)
{
	return (dl->dl_os != NULL);
}
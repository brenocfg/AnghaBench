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
typedef  int /*<<< orphan*/  u_int ;
struct uni {int /*<<< orphan*/ * debug; } ;
typedef  enum uni_verb { ____Placeholder_uni_verb } uni_verb ;

/* Variables and functions */

void
uni_set_debug(struct uni *uni, enum uni_verb fac, u_int level)
{
	uni->debug[fac] = level;
}
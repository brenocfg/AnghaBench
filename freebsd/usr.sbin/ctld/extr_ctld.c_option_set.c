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
struct option {int /*<<< orphan*/  o_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
option_set(struct option *o, const char *value)
{

	free(o->o_value);
	o->o_value = checked_strdup(value);
}
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
struct property {struct property* value; struct property* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct property*) ; 

void dlpar_free_cc_property(struct property *prop)
{
	kfree(prop->name);
	kfree(prop->value);
	kfree(prop);
}
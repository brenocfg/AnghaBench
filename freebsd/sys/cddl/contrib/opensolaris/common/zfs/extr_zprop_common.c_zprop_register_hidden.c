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
typedef  scalar_t__ zprop_type_t ;
typedef  int /*<<< orphan*/  zprop_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ PROP_TYPE_NUMBER ; 
 int /*<<< orphan*/  zprop_register_impl (int,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
zprop_register_hidden(int prop, const char *name, zprop_type_t type,
    zprop_attr_t attr, int objset_types, const char *colname)
{
	zprop_register_impl(prop, name, type, 0, NULL, attr,
	    objset_types, NULL, colname,
	    type == PROP_TYPE_NUMBER, B_FALSE, NULL);
}
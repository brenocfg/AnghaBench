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
struct column_data {char const* prefix; } ;
typedef  TYPE_1__* rtbl_t ;
struct TYPE_3__ {char const* column_prefix; } ;

/* Variables and functions */

__attribute__((used)) static const char *
get_column_prefix (rtbl_t table, struct column_data *c)
{
    if (c == NULL)
	return "";
    if (c->prefix)
	return c->prefix;
    if (table->column_prefix)
	return table->column_prefix;
    return "";
}
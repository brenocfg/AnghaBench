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
struct column_data {char const* suffix; } ;
typedef  int /*<<< orphan*/  rtbl_t ;

/* Variables and functions */

__attribute__((used)) static const char *
get_column_suffix (rtbl_t table, struct column_data *c)
{
    if (c && c->suffix)
	return c->suffix;
    return "";
}
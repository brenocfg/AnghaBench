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
struct testlist_alias_t {int dummy; } ;

/* Variables and functions */
 struct testlist_alias_t const* cfg_aliases ; 

void
tinytest_set_aliases(const struct testlist_alias_t *aliases)
{
	cfg_aliases = aliases;
}
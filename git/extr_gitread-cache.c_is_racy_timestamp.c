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
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  ce_stat_data; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ is_racy_stat (struct index_state const*,int /*<<< orphan*/ *) ; 

int is_racy_timestamp(const struct index_state *istate,
			     const struct cache_entry *ce)
{
	return (!S_ISGITLINK(ce->ce_mode) &&
		is_racy_stat(istate, &ce->ce_stat_data));
}
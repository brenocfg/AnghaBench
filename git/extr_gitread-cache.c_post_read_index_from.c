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

/* Variables and functions */
 int /*<<< orphan*/  check_ce_order (struct index_state*) ; 
 int /*<<< orphan*/  tweak_fsmonitor (struct index_state*) ; 
 int /*<<< orphan*/  tweak_split_index (struct index_state*) ; 
 int /*<<< orphan*/  tweak_untracked_cache (struct index_state*) ; 

__attribute__((used)) static void post_read_index_from(struct index_state *istate)
{
	check_ce_order(istate);
	tweak_untracked_cache(istate);
	tweak_split_index(istate);
	tweak_fsmonitor(istate);
}
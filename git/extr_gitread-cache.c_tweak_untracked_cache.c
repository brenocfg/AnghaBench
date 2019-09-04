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
 int /*<<< orphan*/  add_untracked_cache (struct index_state*) ; 
 int git_config_get_untracked_cache () ; 
 int /*<<< orphan*/  remove_untracked_cache (struct index_state*) ; 

__attribute__((used)) static void tweak_untracked_cache(struct index_state *istate)
{
	switch (git_config_get_untracked_cache()) {
	case -1: /* keep: do nothing */
		break;
	case 0: /* false */
		remove_untracked_cache(istate);
		break;
	case 1: /* true */
		add_untracked_cache(istate);
		break;
	default: /* unknown value: do nothing */
		break;
	}
}
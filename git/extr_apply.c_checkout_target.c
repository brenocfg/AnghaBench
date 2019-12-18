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
struct stat {int dummy; } ;
struct index_state {int dummy; } ;
struct checkout {int refresh_cache; struct index_state* istate; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct checkout CHECKOUT_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ checkout_entry (struct cache_entry*,struct checkout*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int checkout_target(struct index_state *istate,
			   struct cache_entry *ce, struct stat *st)
{
	struct checkout costate = CHECKOUT_INIT;

	costate.refresh_cache = 1;
	costate.istate = istate;
	if (checkout_entry(ce, &costate, NULL, NULL) ||
	    lstat(ce->name, st))
		return error(_("cannot checkout %s"), ce->name);
	return 0;
}
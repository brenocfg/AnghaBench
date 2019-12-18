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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_3__ {int in_hook; } ;
typedef  TYPE_1__ tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/ * tsdn_fetch () ; 
 TYPE_1__* tsdn_tcachep_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool *
hook_reentrantp() {
	/*
	 * We prevent user reentrancy within hooks.  This is basically just a
	 * thread-local bool that triggers an early-exit.
	 *
	 * We don't fold in_hook into reentrancy.  There are two reasons for
	 * this:
	 * - Right now, we turn on reentrancy during things like extent hook
	 *   execution.  Allocating during extent hooks is not officially
	 *   supported, but we don't want to break it for the time being.  These
	 *   sorts of allocations should probably still be hooked, though.
	 * - If a hook allocates, we may want it to be relatively fast (after
	 *   all, it executes on every allocator operation).  Turning on
	 *   reentrancy is a fairly heavyweight mode (disabling tcache,
	 *   redirecting to arena 0, etc.).  It's possible we may one day want
	 *   to turn on reentrant mode here, if it proves too difficult to keep
	 *   this working.  But that's fairly easy for us to see; OTOH, people
	 *   not using hooks because they're too slow is easy for us to miss.
	 *
	 * The tricky part is
	 * that this code might get invoked even if we don't have access to tsd.
	 * This function mimics getting a pointer to thread-local data, except
	 * that it might secretly return a pointer to some global data if we
	 * know that the caller will take the early-exit path.
	 * If we return a bool that indicates that we are reentrant, then the
	 * caller will go down the early exit path, leaving the global
	 * untouched.
	 */
	static bool in_hook_global = true;
	tsdn_t *tsdn = tsdn_fetch();
	tcache_t *tcache = tsdn_tcachep_get(tsdn);
	if (tcache != NULL) {
		return &tcache->in_hook;
	}
	return &in_hook_global;
}
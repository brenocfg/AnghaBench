#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct remote {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ choice; scalar_t__ no_filter; } ;

/* Variables and functions */
 TYPE_1__ filter_options ; 
 int /*<<< orphan*/  has_promisor_remote () ; 
 int /*<<< orphan*/  partial_clone_get_default_filter_spec (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  partial_clone_register (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline void fetch_one_setup_partial(struct remote *remote)
{
	/*
	 * Explicit --no-filter argument overrides everything, regardless
	 * of any prior partial clones and fetches.
	 */
	if (filter_options.no_filter)
		return;

	/*
	 * If no prior partial clone/fetch and the current fetch DID NOT
	 * request a partial-fetch, do a normal fetch.
	 */
	if (!has_promisor_remote() && !filter_options.choice)
		return;

	/*
	 * If this is a partial-fetch request, we enable partial on
	 * this repo if not already enabled and remember the given
	 * filter-spec as the default for subsequent fetches to this
	 * remote.
	 */
	if (filter_options.choice) {
		partial_clone_register(remote->name, &filter_options);
		return;
	}

	/*
	 * Do a partial-fetch from the promisor remote using either the
	 * explicitly given filter-spec or inherit the filter-spec from
	 * the config.
	 */
	if (!filter_options.choice)
		partial_clone_get_default_filter_spec(&filter_options, remote->name);
	return;
}
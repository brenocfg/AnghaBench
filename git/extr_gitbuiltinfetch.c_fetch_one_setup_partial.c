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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 TYPE_1__ filter_options ; 
 int /*<<< orphan*/  partial_clone_get_default_filter_spec (TYPE_1__*) ; 
 int /*<<< orphan*/  partial_clone_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  repository_format_partial_clone ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

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
	if (!repository_format_partial_clone && !filter_options.choice)
		return;

	/*
	 * If this is the FIRST partial-fetch request, we enable partial
	 * on this repo and remember the given filter-spec as the default
	 * for subsequent fetches to this remote.
	 */
	if (!repository_format_partial_clone && filter_options.choice) {
		partial_clone_register(remote->name, &filter_options);
		return;
	}

	/*
	 * We are currently limited to only ONE promisor remote and only
	 * allow partial-fetches from the promisor remote.
	 */
	if (strcmp(remote->name, repository_format_partial_clone)) {
		if (filter_options.choice)
			die(_("--filter can only be used with the remote "
			      "configured in extensions.partialClone"));
		return;
	}

	/*
	 * Do a partial-fetch from the promisor remote using either the
	 * explicitly given filter-spec or inherit the filter-spec from
	 * the config.
	 */
	if (!filter_options.choice)
		partial_clone_get_default_filter_spec(&filter_options);
	return;
}
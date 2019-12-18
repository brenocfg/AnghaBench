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
struct object_id {int dummy; } ;
struct disambiguate_state {int candidate_ok; int /*<<< orphan*/  candidate; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  repo; scalar_t__ (* fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  disambiguate_fn_used; int /*<<< orphan*/  candidate_checked; int /*<<< orphan*/  candidate_exists; scalar_t__ ambiguous; } ;

/* Variables and functions */
 int MISSING_OBJECT ; 
 int SHORT_NAME_AMBIGUOUS ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int finish_object_disambiguation(struct disambiguate_state *ds,
					struct object_id *oid)
{
	if (ds->ambiguous)
		return SHORT_NAME_AMBIGUOUS;

	if (!ds->candidate_exists)
		return MISSING_OBJECT;

	if (!ds->candidate_checked)
		/*
		 * If this is the only candidate, there is no point
		 * calling the disambiguation hint callback.
		 *
		 * On the other hand, if the current candidate
		 * replaced an earlier candidate that did _not_ pass
		 * the disambiguation hint callback, then we do have
		 * more than one objects that match the short name
		 * given, so we should make sure this one matches;
		 * otherwise, if we discovered this one and the one
		 * that we previously discarded in the reverse order,
		 * we would end up showing different results in the
		 * same repository!
		 */
		ds->candidate_ok = (!ds->disambiguate_fn_used ||
				    ds->fn(ds->repo, &ds->candidate, ds->cb_data));

	if (!ds->candidate_ok)
		return SHORT_NAME_AMBIGUOUS;

	oidcpy(oid, &ds->candidate);
	return 0;
}
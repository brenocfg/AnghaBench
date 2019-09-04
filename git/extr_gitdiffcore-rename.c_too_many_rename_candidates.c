#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  find_copies_harder; } ;
struct diff_options {int rename_limit; int needed_rename_limit; TYPE_1__ flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 scalar_t__ diff_unmodified_pair (int /*<<< orphan*/ ) ; 
 TYPE_2__* rename_src ; 
 int rename_src_nr ; 

__attribute__((used)) static int too_many_rename_candidates(int num_create,
				      struct diff_options *options)
{
	int rename_limit = options->rename_limit;
	int num_src = rename_src_nr;
	int i;

	options->needed_rename_limit = 0;

	/*
	 * This basically does a test for the rename matrix not
	 * growing larger than a "rename_limit" square matrix, ie:
	 *
	 *    num_create * num_src > rename_limit * rename_limit
	 */
	if (rename_limit <= 0)
		rename_limit = 32767;
	if ((num_create <= rename_limit || num_src <= rename_limit) &&
	    ((uint64_t)num_create * (uint64_t)num_src
	     <= (uint64_t)rename_limit * (uint64_t)rename_limit))
		return 0;

	options->needed_rename_limit =
		num_src > num_create ? num_src : num_create;

	/* Are we running under -C -C? */
	if (!options->flags.find_copies_harder)
		return 1;

	/* Would we bust the limit if we were running under -C? */
	for (num_src = i = 0; i < rename_src_nr; i++) {
		if (diff_unmodified_pair(rename_src[i].p))
			continue;
		num_src++;
	}
	if ((num_create <= rename_limit || num_src <= rename_limit) &&
	    ((uint64_t)num_create * (uint64_t)num_src
	     <= (uint64_t)rename_limit * (uint64_t)rename_limit))
		return 2;
	return 1;
}
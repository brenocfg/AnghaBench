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
struct ref_iterator {int dummy; } ;
struct prefix_ref_iterator {int /*<<< orphan*/  prefix; scalar_t__ iter0; } ;

/* Variables and functions */
 int ITER_DONE ; 
 int /*<<< orphan*/  base_ref_iterator_free (struct ref_iterator*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int ref_iterator_abort (scalar_t__) ; 

__attribute__((used)) static int prefix_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct prefix_ref_iterator *iter =
		(struct prefix_ref_iterator *)ref_iterator;
	int ok = ITER_DONE;

	if (iter->iter0)
		ok = ref_iterator_abort(iter->iter0);
	free(iter->prefix);
	base_ref_iterator_free(ref_iterator);
	return ok;
}
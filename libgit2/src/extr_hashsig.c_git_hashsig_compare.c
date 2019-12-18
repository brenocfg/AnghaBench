#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_6__ {int opt; TYPE_2__ maxs; TYPE_2__ mins; int /*<<< orphan*/  lines; } ;
typedef  TYPE_1__ git_hashsig ;

/* Variables and functions */
 int GIT_HASHSIG_IGNORE_WHITESPACE ; 
 scalar_t__ HASHSIG_HEAP_SIZE ; 
 int HASHSIG_SCALE ; 
 int hashsig_heap_compare (TYPE_2__*,TYPE_2__*) ; 

int git_hashsig_compare(const git_hashsig *a, const git_hashsig *b)
{
	/* if we have no elements in either file then each file is either
	 * empty or blank.  if we're ignoring whitespace then the files are
	 * similar, otherwise they're dissimilar.
	 */
	if (a->mins.size == 0 && b->mins.size == 0) {
		if ((!a->lines && !b->lines) ||
			(a->opt & GIT_HASHSIG_IGNORE_WHITESPACE))
			return HASHSIG_SCALE;
		else
			return 0;
	}

	/* if we have fewer than the maximum number of elements, then just use
	 * one array since the two arrays will be the same
	 */
	if (a->mins.size < HASHSIG_HEAP_SIZE)
		return hashsig_heap_compare(&a->mins, &b->mins);
	else
		return (hashsig_heap_compare(&a->mins, &b->mins) +
				hashsig_heap_compare(&a->maxs, &b->maxs)) / 2;
}
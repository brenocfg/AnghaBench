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
struct cache_ref_iterator {char* levels; scalar_t__ prefix; } ;

/* Variables and functions */
 int ITER_DONE ; 
 int /*<<< orphan*/  base_ref_iterator_free (struct ref_iterator*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int cache_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;

	free((char *)iter->prefix);
	free(iter->levels);
	base_ref_iterator_free(ref_iterator);
	return ITER_DONE;
}
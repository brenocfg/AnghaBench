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
struct cache_params {int dummy; } ;
struct cache_ {int entries_capacity; scalar_t__ entries_size; int /*<<< orphan*/ * entries; int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int INITIAL_ENTRIES_CAPACITY ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_* (*) (struct cache_params const*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_* (*) (struct cache_params const*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cache_params const*,int) ; 

struct cache_ *
init_cache(struct cache_params const *params)
{
	struct cache_ *retval;

	TRACE_IN(init_cache);
	assert(params != NULL);

	retval = calloc(1, sizeof(*retval));
	assert(retval != NULL);

	assert(params != NULL);
	memcpy(&retval->params, params, sizeof(struct cache_params));

	retval->entries = calloc(INITIAL_ENTRIES_CAPACITY,
		sizeof(*retval->entries));
	assert(retval->entries != NULL);

	retval->entries_capacity = INITIAL_ENTRIES_CAPACITY;
	retval->entries_size = 0;

	TRACE_OUT(init_cache);
	return (retval);
}
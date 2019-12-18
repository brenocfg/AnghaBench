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
struct configuration {int entries_capacity; int /*<<< orphan*/  rwlock; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int INITIAL_ENTRIES_CAPACITY ; 
 int /*<<< orphan*/  TRACE_IN (struct configuration* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct configuration* (*) ()) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct configuration *
init_configuration(void)
{
	struct configuration	*retval;

	TRACE_IN(init_configuration);
	retval = calloc(1, sizeof(*retval));
	assert(retval != NULL);

	retval->entries_capacity = INITIAL_ENTRIES_CAPACITY;
	retval->entries = calloc(retval->entries_capacity,
		sizeof(*retval->entries));
	assert(retval->entries != NULL);

	pthread_rwlock_init(&retval->rwlock, NULL);

	TRACE_OUT(init_configuration);
	return (retval);
}
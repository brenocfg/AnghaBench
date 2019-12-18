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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_4__ {int /*<<< orphan*/  prof_data; } ;
typedef  TYPE_1__ malloc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_prof_data_init (int /*<<< orphan*/ *) ; 

void
malloc_mutex_prof_data_reset(tsdn_t *tsdn, malloc_mutex_t *mutex) {
	malloc_mutex_assert_owner(tsdn, mutex);
	mutex_prof_data_init(&mutex->prof_data);
}
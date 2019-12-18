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
struct configuration {int /*<<< orphan*/  rwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*)) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 

void
configuration_lock_rdlock(struct configuration *config)
{
    TRACE_IN(configuration_lock_rdlock);
    pthread_rwlock_rdlock(&config->rwlock);
    TRACE_OUT(configuration_lock_rdlock);
}
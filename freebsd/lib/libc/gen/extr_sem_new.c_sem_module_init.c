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

/* Variables and functions */
 int /*<<< orphan*/  _pthread_atfork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_child_postfork ; 
 int /*<<< orphan*/  sem_llock ; 
 int /*<<< orphan*/  sem_postfork ; 
 int /*<<< orphan*/  sem_prefork ; 

__attribute__((used)) static void
sem_module_init(void)
{

	_pthread_mutex_init(&sem_llock, NULL);
	_pthread_atfork(sem_prefork, sem_postfork, sem_child_postfork);
}
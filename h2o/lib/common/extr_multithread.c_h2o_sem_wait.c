#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ _cur; int /*<<< orphan*/  _mutex; int /*<<< orphan*/  _cond; } ;
typedef  TYPE_1__ h2o_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void h2o_sem_wait(h2o_sem_t *sem)
{
    pthread_mutex_lock(&sem->_mutex);
    while (sem->_cur <= 0)
        pthread_cond_wait(&sem->_cond, &sem->_mutex);
    --sem->_cur;
    pthread_mutex_unlock(&sem->_mutex);
}
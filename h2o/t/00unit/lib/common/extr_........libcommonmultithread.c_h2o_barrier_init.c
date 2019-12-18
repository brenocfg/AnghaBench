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
struct TYPE_3__ {size_t _count; size_t _out_of_wait; int /*<<< orphan*/  _cond; int /*<<< orphan*/  _mutex; } ;
typedef  TYPE_1__ h2o_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void h2o_barrier_init(h2o_barrier_t *barrier, size_t count)
{
    pthread_mutex_init(&barrier->_mutex, NULL);
    pthread_cond_init(&barrier->_cond, NULL);
    barrier->_count = count;
    barrier->_out_of_wait = count;
}
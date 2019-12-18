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
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_3__ {int lock; int /*<<< orphan*/  a_mutex; int /*<<< orphan*/ * owner; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ pt_mutex_t ;

/* Variables and functions */
 TYPE_1__ global_lock ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_equal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  threaded ; 

void ThreadLock( void ){
	pt_mutex_t *pt_mutex = &global_lock;

	if ( !threaded ) {
		return;
	}

	pthread_mutex_lock( &pt_mutex->a_mutex );
	if ( pthread_equal( pthread_self(), (pthread_t)&pt_mutex->owner ) ) {
		pt_mutex->lock++;
	}
	else
	{
		if ( ( !pt_mutex->owner ) && ( pt_mutex->lock == 0 ) ) {
			pt_mutex->owner = (pthread_t *)pthread_self();
			pt_mutex->lock  = 1;
		}
		else
		{
			while ( 1 )
			{
				pthread_cond_wait( &pt_mutex->cond, &pt_mutex->a_mutex );
				if ( ( !pt_mutex->owner ) && ( pt_mutex->lock == 0 ) ) {
					pt_mutex->owner = (pthread_t *)pthread_self();
					pt_mutex->lock  = 1;
					break;
				}
			}
		}
	}
	pthread_mutex_unlock( &pt_mutex->a_mutex );
}
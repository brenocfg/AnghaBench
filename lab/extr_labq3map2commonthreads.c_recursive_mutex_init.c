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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_3__ {scalar_t__ lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  a_mutex; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_1__ pt_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 TYPE_1__ global_lock ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void recursive_mutex_init( pthread_mutexattr_t attribs ){
	pt_mutex_t *pt_mutex = &global_lock;

	pt_mutex->owner = NULL;
	if ( pthread_mutex_init( &pt_mutex->a_mutex, &attribs ) != 0 ) {
		Error( "pthread_mutex_init failed\n" );
	}
	if ( pthread_cond_init( &pt_mutex->cond, NULL ) != 0 ) {
		Error( "pthread_cond_init failed\n" );
	}

	pt_mutex->lock = 0;
}
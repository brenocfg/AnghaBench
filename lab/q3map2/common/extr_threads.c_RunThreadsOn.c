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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int I_FloatTime () ; 
 int MAX_THREADS ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_ADAPTIVE_NP ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_FAST_NP ; 
 int /*<<< orphan*/  Sys_Printf (char*,int) ; 
 scalar_t__ dispatch ; 
 int numthreads ; 
 int oldf ; 
 scalar_t__ pacifier ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  recursive_mutex_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  threaded ; 
 int workcount ; 

void RunThreadsOn( int workcnt, qboolean showpacifier, void ( *func )( int ) ){
	pthread_mutexattr_t mattrib;
	pthread_t work_threads[MAX_THREADS];

	int start, end;
	int i = 0;
	void *exit_value;

	start     = I_FloatTime();
	pacifier  = showpacifier;

	dispatch  = 0;
	oldf      = -1;
	workcount = workcnt;

	if ( numthreads == 1 ) {
		func( 0 );
	}
	else
	{
		threaded  = qtrue;

		if ( pacifier ) {
			setbuf( stdout, NULL );
		}

		if ( pthread_mutexattr_init( &mattrib ) != 0 ) {
			Error( "pthread_mutexattr_init failed" );
		}
#if __GLIBC_MINOR__ == 1
		if ( pthread_mutexattr_settype( &mattrib, PTHREAD_MUTEX_FAST_NP ) != 0 )
#else
		if ( pthread_mutexattr_settype( &mattrib, PTHREAD_MUTEX_ADAPTIVE_NP ) != 0 )
#endif
		{ Error( "pthread_mutexattr_settype failed" ); }
		recursive_mutex_init( mattrib );

		for ( i = 0 ; i < numthreads ; i++ )
		{
			/* Default pthread attributes: joinable & non-realtime scheduling */
			if ( pthread_create( &work_threads[i], NULL, (void*)func, (void*)(uintptr_t)i ) != 0 ) {
				Error( "pthread_create failed" );
			}
		}
		for ( i = 0 ; i < numthreads ; i++ )
		{
			if ( pthread_join( work_threads[i], &exit_value ) != 0 ) {
				Error( "pthread_join failed" );
			}
		}
		pthread_mutexattr_destroy( &mattrib );
		threaded = qfalse;
	}

	end = I_FloatTime();
	if ( pacifier ) {
		Sys_Printf( " (%i)\n", end - start );
	}
}
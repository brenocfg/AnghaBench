#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int tv_sec; int tv_usec; } ;
struct TYPE_4__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double cfg_connlimit ; 
 double cfg_grouplimit ; 
 scalar_t__ cfg_help ; 
 TYPE_3__ cfg_tick ; 
 int cfg_tick_msec ; 
 int /*<<< orphan*/  evthread_enable_lock_debugging () ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_weakrand_seed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ handle_option (int,char**,int*,TYPE_1__*) ; 
 TYPE_1__* options ; 
 double seconds_per_tick ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 int test_ratelimiting () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  weakrand_state ; 

int
main(int argc, char **argv)
{
	int i,j;
	double ratio;

#ifdef _WIN32
	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

	evutil_weakrand_seed_(&weakrand_state, 0);

#ifndef _WIN32
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif
	for (i = 1; i < argc; ++i) {
		for (j = 0; options[j].name; ++j) {
			if (!strcmp(argv[i],options[j].name)) {
				if (handle_option(argc,argv,&i,&options[j])<0)
					return 1;
				goto again;
			}
		}
		fprintf(stderr, "Unknown option '%s'\n", argv[i]);
		usage();
		return 1;
	again:
		;
	}
	if (cfg_help) {
		usage();
		return 0;
	}

	cfg_tick.tv_sec = cfg_tick_msec / 1000;
	cfg_tick.tv_usec = (cfg_tick_msec % 1000)*1000;

	seconds_per_tick = ratio = cfg_tick_msec / 1000.0;

	cfg_connlimit *= ratio;
	cfg_grouplimit *= ratio;

	{
		struct timeval tv;
		evutil_gettimeofday(&tv, NULL);
#ifdef _WIN32
		srand(tv.tv_usec);
#else
		srandom(tv.tv_usec);
#endif
	}

#ifndef EVENT__DISABLE_THREAD_SUPPORT
	evthread_enable_lock_debugging();
#endif

	return test_ratelimiting();
}
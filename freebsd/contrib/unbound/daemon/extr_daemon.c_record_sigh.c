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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
#define  SIGBREAK 133 
#define  SIGHUP 132 
#define  SIGINT 131 
#define  SIGPIPE 130 
#define  SIGQUIT 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sig_record_quit ; 
 int /*<<< orphan*/  sig_record_reload ; 

__attribute__((used)) static RETSIGTYPE record_sigh(int sig)
{
#ifdef LIBEVENT_SIGNAL_PROBLEM
	/* cannot log, verbose here because locks may be held */
	/* quit on signal, no cleanup and statistics, 
	   because installed libevent version is not threadsafe */
	exit(0);
#endif 
	switch(sig)
	{
		case SIGTERM:
#ifdef SIGQUIT
		case SIGQUIT:
#endif
#ifdef SIGBREAK
		case SIGBREAK:
#endif
		case SIGINT:
			sig_record_quit++;
			break;
#ifdef SIGHUP
		case SIGHUP:
			sig_record_reload++;
			break;
#endif
#ifdef SIGPIPE
		case SIGPIPE:
			break;
#endif
		default:
			/* ignoring signal */
			break;
	}
}
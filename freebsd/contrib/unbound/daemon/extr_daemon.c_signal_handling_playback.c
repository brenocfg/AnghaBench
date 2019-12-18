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
struct worker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ sig_record_quit ; 
 scalar_t__ sig_record_reload ; 
 int /*<<< orphan*/  worker_sighandler (int /*<<< orphan*/ ,struct worker*) ; 

__attribute__((used)) static void
signal_handling_playback(struct worker* wrk)
{
#ifdef SIGHUP
	if(sig_record_reload)
		worker_sighandler(SIGHUP, wrk);
#endif
	if(sig_record_quit)
		worker_sighandler(SIGTERM, wrk);
	sig_record_quit = 0;
	sig_record_reload = 0;
}
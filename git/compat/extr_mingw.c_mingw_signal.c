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
typedef  int /*<<< orphan*/  sig_handler_t ;

/* Variables and functions */
#define  SIGALRM 129 
#define  SIGINT 128 
 int /*<<< orphan*/  sigint_fn ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_fn ; 

sig_handler_t mingw_signal(int sig, sig_handler_t handler)
{
	sig_handler_t old;

	switch (sig) {
	case SIGALRM:
		old = timer_fn;
		timer_fn = handler;
		break;

	case SIGINT:
		old = sigint_fn;
		sigint_fn = handler;
		break;

	default:
		return signal(sig, handler);
	}

	return old;
}
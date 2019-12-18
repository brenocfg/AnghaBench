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
struct thread {int dummy; } ;
struct nlm_feedback_arg {int dummy; } ;

/* Variables and functions */
#define  FEEDBACK_OK 130 
#define  FEEDBACK_RECONNECT 129 
#define  FEEDBACK_REXMIT2 128 
 struct thread* curthread ; 
 int /*<<< orphan*/  nlm_down (struct nlm_feedback_arg*,struct thread*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_up (struct nlm_feedback_arg*,struct thread*,char*) ; 

__attribute__((used)) static void
nlm_feedback(int type, int proc, void *arg)
{
	struct thread *td = curthread;
	struct nlm_feedback_arg *nf = (struct nlm_feedback_arg *) arg;

	switch (type) {
	case FEEDBACK_REXMIT2:
	case FEEDBACK_RECONNECT:
		nlm_down(nf, td, "lockd not responding", 0);
		break;

	case FEEDBACK_OK:
		nlm_up(nf, td, "lockd is alive again");
		break;
	}
}
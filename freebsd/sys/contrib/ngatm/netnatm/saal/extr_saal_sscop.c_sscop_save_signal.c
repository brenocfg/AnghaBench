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
typedef  int /*<<< orphan*/  u_int ;
struct sscop_sig {struct sscop_msg* msg; int /*<<< orphan*/  sig; } ;
struct sscop_msg {int dummy; } ;
struct sscop {int /*<<< orphan*/  saved_sigs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE (char*) ; 
 int /*<<< orphan*/  SIGQ_APPEND (int /*<<< orphan*/ *,struct sscop_sig*) ; 
 int /*<<< orphan*/  SIG_ALLOC (struct sscop_sig*) ; 
 int /*<<< orphan*/  SSCOP_MSG_FREE (struct sscop_msg*) ; 

__attribute__((used)) static void
sscop_save_signal(struct sscop *sscop, u_int sig, struct sscop_msg *msg)
{
	struct sscop_sig *s;

	SIG_ALLOC(s);
	if(s == NULL) {
		FAILURE("sscop: cannot allocate signal");
		SSCOP_MSG_FREE(msg);
		return;
	}
	s->sig = sig;
	s->msg = msg;
	SIGQ_APPEND(&sscop->saved_sigs, s);
}
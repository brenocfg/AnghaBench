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
struct sscop_sig {int /*<<< orphan*/  msg; int /*<<< orphan*/  sig; } ;
struct sscop {int /*<<< orphan*/  in_sig; int /*<<< orphan*/  sigs; } ;
typedef  int /*<<< orphan*/  sscop_sigq_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGQ_APPEND (int /*<<< orphan*/ *,struct sscop_sig*) ; 
 struct sscop_sig* SIGQ_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGQ_MOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGQ_PREPEND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIG_FREE (struct sscop_sig*) ; 
 scalar_t__ sig_exec (struct sscop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_sigs(struct sscop *sscop)
{
	struct sscop_sig *s;
	sscop_sigq_head_t dsigs, q;
	int exec;

	sscop->in_sig++;
 
	/*
	 * Copy the current signal queue to the local one and empty
	 * the signal queue. Then loop through the signals. After one
	 * pass we have a list of delayed signals because of entry
	 * conditions and a new list of signals. Merge them. Repeat until
	 * the signal queue is either empty or contains only delayed signals.
	 */
	SIGQ_INIT(&q);
	SIGQ_INIT(&dsigs);
	do {
		exec = 0;

		/*
		 * Copy signal list and make sscop list empty
		 */
		SIGQ_MOVE(&sscop->sigs, &q);

		/*
		 * Loop through the list
		 */
		while((s = SIGQ_GET(&q)) != NULL) {
			if(sig_exec(sscop, s->sig, s->msg)) {
				exec = 1;
				SIG_FREE(s);
			} else {
				SIGQ_APPEND(&dsigs, s);
			}
		}

		/*
		 * Merge lists by inserting delayed signals in front of
		 * the signal list. preserving the order.
		 */
		SIGQ_PREPEND(&dsigs, &sscop->sigs);
	} while(exec);
	sscop->in_sig--;
}
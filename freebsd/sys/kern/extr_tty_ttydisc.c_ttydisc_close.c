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
struct tty {int t_flags; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int TF_HIWAT ; 
 int TF_STOPPED ; 
 int TF_ZOMBIE ; 
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  tty_flush (struct tty*,int) ; 
 int /*<<< orphan*/  ttyhook_close (struct tty*) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 

void
ttydisc_close(struct tty *tp)
{

	/* Clean up our flags when leaving the discipline. */
	tp->t_flags &= ~(TF_STOPPED|TF_HIWAT|TF_ZOMBIE);

	/*
	 * POSIX states that we must drain output and flush input on
	 * last close.  Draining has already been done if possible.
	 */
	tty_flush(tp, FREAD | FWRITE);

	if (ttyhook_hashook(tp, close))
		ttyhook_close(tp);
}
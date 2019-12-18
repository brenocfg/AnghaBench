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
struct tty {int /*<<< orphan*/  t_inq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTWERASE ; 
 scalar_t__ CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CTL_ALNUM (char) ; 
 scalar_t__ CTL_WHITE (char) ; 
 int /*<<< orphan*/  l ; 
 int /*<<< orphan*/  ttydisc_rubchar (struct tty*) ; 
 scalar_t__ ttyinq_peekchar (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static void
ttydisc_rubword(struct tty *tp)
{
	char c;
	int quote, alnum;

	/* Strip whitespace first. */
	for (;;) {
		if (ttyinq_peekchar(&tp->t_inq, &c, &quote) != 0)
			return;
		if (!CTL_WHITE(c))
			break;
		ttydisc_rubchar(tp);
	}

	/*
	 * Record whether the last character from the previous iteration
	 * was alphanumeric or not. We need this to implement ALTWERASE.
	 */
	alnum = CTL_ALNUM(c);
	for (;;) {
		ttydisc_rubchar(tp);

		if (ttyinq_peekchar(&tp->t_inq, &c, &quote) != 0)
			return;
		if (CTL_WHITE(c))
			return;
		if (CMP_FLAG(l, ALTWERASE) && CTL_ALNUM(c) != alnum)
			return;
	}
}
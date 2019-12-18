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
struct tty {int dummy; } ;
struct pts_softc {int pts_flags; } ;
struct knote {int /*<<< orphan*/  kn_data; int /*<<< orphan*/  kn_flags; struct file* kn_fp; } ;
struct file {struct tty* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 int PTS_FINISHED ; 
 struct pts_softc* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_getc_poll (struct tty*) ; 

__attribute__((used)) static int
pts_kqops_read_event(struct knote *kn, long hint)
{
	struct file *fp = kn->kn_fp;
	struct tty *tp = fp->f_data;
	struct pts_softc *psc = tty_softc(tp);

	if (psc->pts_flags & PTS_FINISHED) {
		kn->kn_flags |= EV_EOF;
		return (1);
	} else {
		kn->kn_data = ttydisc_getc_poll(tp);
		return (kn->kn_data > 0);
	}
}
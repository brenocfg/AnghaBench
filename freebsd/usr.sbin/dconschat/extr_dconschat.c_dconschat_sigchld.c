#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kevent {int dummy; } ;
struct dcons_port {int /*<<< orphan*/  infd; int /*<<< orphan*/  outfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  zero; int /*<<< orphan*/  kq; int /*<<< orphan*/  traw; struct dcons_port* port; } ;

/* Variables and functions */
 size_t DCONS_CON ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  NOTE_LOWAT ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ sc ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ tc_set ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dconschat_sigchld(int s)
{
	struct kevent kev;
	struct dcons_port *p;
	char buf[256];

	p = &sc.port[DCONS_CON];

	snprintf(buf, 256, "\r\n[child exit]\r\n");
	write(p->outfd, buf, strlen(buf));

	if (tc_set)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &sc.traw);

	EV_SET(&kev, p->infd, EVFILT_READ, EV_ADD, NOTE_LOWAT, 1, (void *)p);
	kevent(sc.kq, &kev, 1, NULL, 0, &sc.zero);
}
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
struct kevent {int dummy; } ;
struct dcons_state {int flags; int /*<<< orphan*/  zero; int /*<<< orphan*/  kq; } ;
struct dcons_port {int infd; int outfd; int s; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  rbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int EV_ADD ; 
 int EV_DELETE ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int F_READY ; 
 int MAX_XFER ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dconschat_read_filter (struct dcons_state*,struct dcons_port*,char*,int,char*,int*) ; 
 int /*<<< orphan*/  dconschat_write_dcons (struct dcons_state*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int verbose ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dconschat_read_socket(struct dcons_state *dc, struct dcons_port *p)
{
	struct kevent kev;
	int len, wlen;
	char rbuf[MAX_XFER], wbuf[MAX_XFER+2];

	if ((len = read(p->infd, rbuf, sizeof(rbuf))) > 0) {
		wlen = 0;
		dconschat_read_filter(dc, p, rbuf, len, wbuf, &wlen);
		/* XXX discard if not ready*/
		if (wlen > 0 && (dc->flags & F_READY) != 0) {
			dconschat_write_dcons(dc, p->port, wbuf, wlen);
			if (verbose > 1) {
				wbuf[wlen] = 0;
				printf("-> %s\n", wbuf);
			} else if (verbose == 1) {
				printf("(%d)", wlen);
				fflush(stdout);
			}
		}
	} else {
		if (verbose) {
			if (len == 0)
				warnx("port%d: closed", p->port);
			else
				warn("port%d: read", p->port);
		}
		EV_SET(&kev, p->infd, EVFILT_READ,
			EV_DELETE, 0, 0, NULL);
		kevent(dc->kq, &kev, 1, NULL, 0, &dc->zero);
		close(p->infd);
		close(p->outfd);
		/* XXX exit for pipe case XXX */
		EV_SET(&kev, p->s, EVFILT_READ,
				EV_ADD | EV_ONESHOT, 0, 0, (void *) p);
		kevent(dc->kq, &kev, 1, NULL, 0, &dc->zero);
		p->infd = p->outfd = -1;
	}
	return(0);
}
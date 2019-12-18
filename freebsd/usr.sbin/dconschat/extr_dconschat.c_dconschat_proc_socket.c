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
struct kevent {scalar_t__ ident; scalar_t__ udata; } ;
struct dcons_state {int /*<<< orphan*/  to; int /*<<< orphan*/  kq; } ;
struct dcons_port {scalar_t__ s; } ;

/* Variables and functions */
 int NEVENT ; 
 int /*<<< orphan*/  dconschat_accept_socket (struct dcons_state*,struct dcons_port*) ; 
 int /*<<< orphan*/  dconschat_read_socket (struct dcons_state*,struct dcons_port*) ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dconschat_proc_socket(struct dcons_state *dc)
{
	struct kevent elist[NEVENT], *e;
	int i, n;
	struct dcons_port *p;

	n = kevent(dc->kq, NULL, 0, elist, NEVENT, &dc->to);
	for (i = 0; i < n; i ++) {
		e = &elist[i];
		p = (struct dcons_port *)e->udata;
		if (e->ident == p->s) {
			dconschat_accept_socket(dc, p);
		} else {
			dconschat_read_socket(dc, p);
		}
	}
	return(0);
}
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
struct dcons_state {int flags; struct dcons_port* port; } ;
struct dcons_port {scalar_t__ infd; int /*<<< orphan*/  outfd; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int DCONS_NPORT ; 
 int F_ONE_SHOT ; 
 int MAX_XFER ; 
 int /*<<< orphan*/  dconschat_cleanup (int /*<<< orphan*/ ) ; 
 int dconschat_get_ptr (struct dcons_state*) ; 
 int dconschat_read_dcons (struct dcons_state*,int,char*,int) ; 
 int /*<<< orphan*/  dconschat_write_socket (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
dconschat_proc_dcons(struct dcons_state *dc)
{
	int port, len, err;
	char buf[MAX_XFER];
	struct dcons_port *p;

	err = dconschat_get_ptr(dc);
	if (err) {
		/* XXX we should stop write operation too. */
		return err;
	}
	for (port = 0; port < DCONS_NPORT; port ++) {
		p = &dc->port[port];
		if (p->infd < 0)
			continue;
		while ((len = dconschat_read_dcons(dc, port, buf,
		    sizeof(buf))) > 0) {
			dconschat_write_socket(p->outfd, buf, len);
			if ((err = dconschat_get_ptr(dc)))
				return (err);
		}
		if ((dc->flags & F_ONE_SHOT) != 0 && len <= 0)
			dconschat_cleanup(0);
	}
	return 0;
}
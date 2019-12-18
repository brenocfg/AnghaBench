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
struct netmap_priv_d {int dummy; } ;
struct knote {struct netmap_priv_d* kn_hook; } ;

/* Variables and functions */
 int netmap_poll (struct netmap_priv_d*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
netmap_knrw(struct knote *kn, long hint, int events)
{
	struct netmap_priv_d *priv;
	int revents;

	if (hint != 0) {
		/* Called from netmap_notify(), typically from a
		 * thread different from the one issuing kevent().
		 * Assume we are ready. */
		return 1;
	}

	/* Called from kevent(). */
	priv = kn->kn_hook;
	revents = netmap_poll(priv, events, /*thread=*/NULL);

	return (events & revents) ? 1 : 0;
}
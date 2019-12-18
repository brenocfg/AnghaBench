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
struct p2p_data {unsigned int ext_listen_period; unsigned int ext_listen_interval; unsigned int ext_listen_interval_sec; unsigned int ext_listen_interval_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,unsigned int,int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  p2p_ext_listen_timeout ; 

int p2p_ext_listen(struct p2p_data *p2p, unsigned int period,
		   unsigned int interval)
{
	if (period > 65535 || interval > 65535 || period > interval ||
	    (period == 0 && interval > 0) || (period > 0 && interval == 0)) {
		p2p_dbg(p2p, "Invalid Extended Listen Timing request: period=%u interval=%u",
			period, interval);
		return -1;
	}

	eloop_cancel_timeout(p2p_ext_listen_timeout, p2p, NULL);

	if (interval == 0) {
		p2p_dbg(p2p, "Disabling Extended Listen Timing");
		p2p->ext_listen_period = 0;
		p2p->ext_listen_interval = 0;
		return 0;
	}

	p2p_dbg(p2p, "Enabling Extended Listen Timing: period %u msec, interval %u msec",
		period, interval);
	p2p->ext_listen_period = period;
	p2p->ext_listen_interval = interval;
	p2p->ext_listen_interval_sec = interval / 1000;
	p2p->ext_listen_interval_usec = (interval % 1000) * 1000;

	eloop_register_timeout(p2p->ext_listen_interval_sec,
			       p2p->ext_listen_interval_usec,
			       p2p_ext_listen_timeout, p2p, NULL);

	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct p2p_data {scalar_t__ drv_in_listen; scalar_t__ in_listen; TYPE_1__* cfg; } ;
struct TYPE_2__ {int (* send_action ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int,int*) ;int /*<<< orphan*/  cb_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  p2p_stop_listen_for_freq (struct p2p_data*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int,int*) ; 

int p2p_send_action(struct p2p_data *p2p, unsigned int freq, const u8 *dst,
		    const u8 *src, const u8 *bssid, const u8 *buf,
		    size_t len, unsigned int wait_time)
{
	int res, scheduled;

	res = p2p->cfg->send_action(p2p->cfg->cb_ctx, freq, dst, src, bssid,
				    buf, len, wait_time, &scheduled);
	if (res == 0 && scheduled && p2p->in_listen && freq > 0 &&
	    (unsigned int) p2p->drv_in_listen != freq) {
		p2p_dbg(p2p,
			"Stop listen on %d MHz to allow a frame to be sent immediately on %d MHz",
			p2p->drv_in_listen, freq);
		p2p_stop_listen_for_freq(p2p, freq);
	}
	return res;
}
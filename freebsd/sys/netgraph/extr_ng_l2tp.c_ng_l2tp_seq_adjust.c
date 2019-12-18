#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct ng_l2tp_config {scalar_t__ peer_win; int /*<<< orphan*/  enabled; } ;
struct l2tp_seq {scalar_t__ wmax; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_4__ {struct l2tp_seq seq; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ L2TP_MAX_XWIN ; 
 int /*<<< orphan*/  ng_l2tp_seq_reset (TYPE_1__*) ; 

__attribute__((used)) static int
ng_l2tp_seq_adjust(priv_p priv, const struct ng_l2tp_config *conf)
{
	struct l2tp_seq *const seq = &priv->seq;
	u_int16_t new_wmax;

	/* If disabling node, reset state sequence number */
	if (!conf->enabled) {
		ng_l2tp_seq_reset(priv);
		return (0);
	}

	/* Adjust peer's max recv window; it can only increase */
	new_wmax = conf->peer_win;
	if (new_wmax > L2TP_MAX_XWIN)
		new_wmax = L2TP_MAX_XWIN;
	if (new_wmax == 0)
		return (EINVAL);
	if (new_wmax < seq->wmax)
		return (EBUSY);
	seq->wmax = new_wmax;

	/* Done */
	return (0);
}
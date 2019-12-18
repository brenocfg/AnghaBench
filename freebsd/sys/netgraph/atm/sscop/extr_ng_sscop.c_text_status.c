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
typedef  char* uintmax_t ;
typedef  int /*<<< orphan*/  u_int ;
struct sbuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ data_delivered; scalar_t__ errors; scalar_t__ maa_dropped; scalar_t__ maa_signals; scalar_t__ aa_dropped; scalar_t__ aa_signals; scalar_t__ out_dropped; scalar_t__ out_packets; scalar_t__ in_dropped; scalar_t__ in_packets; } ;
struct priv {int /*<<< orphan*/  sscop; TYPE_1__ stats; int /*<<< orphan*/  enabled; scalar_t__ manage; scalar_t__ lower; scalar_t__ upper; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NAME (scalar_t__) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 scalar_t__ NG_HOOK_PEER (scalar_t__) ; 
 int /*<<< orphan*/  NG_NODE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int sbuf_len (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  sscop_getstate (int /*<<< orphan*/ ) ; 
 char* sscop_statename (int /*<<< orphan*/ ) ; 
 char* sscop_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
text_status(node_p node, struct priv *priv, char *arg, u_int len)
{
	struct sbuf sbuf;

	sbuf_new(&sbuf, arg, len, 0);

	if (priv->upper)
		sbuf_printf(&sbuf, "upper hook: %s connected to %s:%s\n",
		    NG_HOOK_NAME(priv->upper),
		    NG_NODE_NAME(NG_HOOK_NODE(NG_HOOK_PEER(priv->upper))),
		    NG_HOOK_NAME(NG_HOOK_PEER(priv->upper)));
	else
		sbuf_printf(&sbuf, "upper hook: <not connected>\n");

	if (priv->lower)
		sbuf_printf(&sbuf, "lower hook: %s connected to %s:%s\n",
		    NG_HOOK_NAME(priv->lower),
		    NG_NODE_NAME(NG_HOOK_NODE(NG_HOOK_PEER(priv->lower))),
		    NG_HOOK_NAME(NG_HOOK_PEER(priv->lower)));
	else
		sbuf_printf(&sbuf, "lower hook: <not connected>\n");

	if (priv->manage)
		sbuf_printf(&sbuf, "manage hook: %s connected to %s:%s\n",
		    NG_HOOK_NAME(priv->manage),
		    NG_NODE_NAME(NG_HOOK_NODE(NG_HOOK_PEER(priv->manage))),
		    NG_HOOK_NAME(NG_HOOK_PEER(priv->manage)));
	else
		sbuf_printf(&sbuf, "manage hook: <not connected>\n");

	sbuf_printf(&sbuf, "sscop state: %s\n",
	    !priv->enabled ? "<disabled>" :
	    sscop_statename(sscop_getstate(priv->sscop)));

	sbuf_printf(&sbuf, "input packets:  %ju\n",
	    (uintmax_t)priv->stats.in_packets);
	sbuf_printf(&sbuf, "input dropped:  %ju\n",
	    (uintmax_t)priv->stats.in_dropped);
	sbuf_printf(&sbuf, "output packets: %ju\n",
	    (uintmax_t)priv->stats.out_packets);
	sbuf_printf(&sbuf, "output dropped: %ju\n",
	    (uintmax_t)priv->stats.out_dropped);
	sbuf_printf(&sbuf, "aa signals:     %ju\n",
	    (uintmax_t)priv->stats.aa_signals);
	sbuf_printf(&sbuf, "aa dropped:     %ju\n",
	    (uintmax_t)priv->stats.aa_dropped);
	sbuf_printf(&sbuf, "maa signals:    %ju\n",
	    (uintmax_t)priv->stats.maa_signals);
	sbuf_printf(&sbuf, "maa dropped:    %ju\n",
	    (uintmax_t)priv->stats.maa_dropped);
	sbuf_printf(&sbuf, "errors:         %ju\n",
	    (uintmax_t)priv->stats.errors);
	sbuf_printf(&sbuf, "data delivered: %ju\n",
	    (uintmax_t)priv->stats.data_delivered);
	sbuf_printf(&sbuf, "window:         %u\n",
	    sscop_window(priv->sscop, 0));

	sbuf_finish(&sbuf);
	return (sbuf_len(&sbuf));
}
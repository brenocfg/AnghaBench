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
typedef  int /*<<< orphan*/  u_int ;
struct sbuf {int dummy; } ;
struct priv {scalar_t__ enabled; int /*<<< orphan*/  sscf; scalar_t__ lower; scalar_t__ upper; } ;
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
 int /*<<< orphan*/  sscfu_getstate (int /*<<< orphan*/ ) ; 
 char* sscfu_statename (int /*<<< orphan*/ ) ; 

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

	sbuf_printf(&sbuf, "sscf state: %s\n",
	    priv->enabled == 0 ? "<disabled>" :
	    sscfu_statename(sscfu_getstate(priv->sscf)));

	sbuf_finish(&sbuf);
	return (sbuf_len(&sbuf));
}
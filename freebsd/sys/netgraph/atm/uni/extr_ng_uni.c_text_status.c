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
typedef  scalar_t__ u_int ;
struct sbuf {int dummy; } ;
struct priv {scalar_t__ uni; int /*<<< orphan*/ * upper; int /*<<< orphan*/ * lower; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_PEER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ UNI_MAXFACILITY ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int sbuf_len (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  uni_facname (scalar_t__) ; 
 scalar_t__ uni_get_debug (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uni_status (scalar_t__,struct sbuf*) ; 

__attribute__((used)) static int
text_status(node_p node, struct priv *priv, char *buf, u_int len)
{
	struct sbuf sbuf;
	u_int f;

	sbuf_new(&sbuf, buf, len, 0);

	if (priv->lower != NULL)
		sbuf_printf(&sbuf, "lower hook: connected to %s:%s\n",
		    NG_NODE_NAME(NG_HOOK_NODE(NG_HOOK_PEER(priv->lower))),
		    NG_HOOK_NAME(NG_HOOK_PEER(priv->lower)));
	else
		sbuf_printf(&sbuf, "lower hook: <not connected>\n");

	if (priv->upper != NULL)
		sbuf_printf(&sbuf, "upper hook: connected to %s:%s\n",
		    NG_NODE_NAME(NG_HOOK_NODE(NG_HOOK_PEER(priv->upper))),
		    NG_HOOK_NAME(NG_HOOK_PEER(priv->upper)));
	else
		sbuf_printf(&sbuf, "upper hook: <not connected>\n");

	sbuf_printf(&sbuf, "debugging:");
	for (f = 0; f < UNI_MAXFACILITY; f++)
		if (uni_get_debug(priv->uni, f) != 0)
			sbuf_printf(&sbuf, " %s=%u", uni_facname(f),
			    uni_get_debug(priv->uni, f));
	sbuf_printf(&sbuf, "\n");

	if (priv->uni)
		uni_status(priv->uni, &sbuf);

	sbuf_finish(&sbuf);
	return (sbuf_len(&sbuf));
}
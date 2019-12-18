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
struct uni_msg {int dummy; } ;
struct uni {int dummy; } ;
struct sscfu_arg {int sig; } ;
struct priv {int /*<<< orphan*/ * lower; int /*<<< orphan*/  uni; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  enum saal_sig { ____Placeholder_saal_sig } saal_sig ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  UNI_FAC_SAAL ; 
 int /*<<< orphan*/  dump_saal_signal (int /*<<< orphan*/ ,int,struct uni_msg*,int) ; 
 scalar_t__ uni_get_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 struct mbuf* uni_msg_pack_mbuf (struct uni_msg*,struct sscfu_arg*,int) ; 

__attribute__((used)) static void
uni_saal_output(struct uni *uni, void *varg, enum saal_sig sig, struct uni_msg *msg)
{
	node_p node = (node_p)varg;
	struct priv *priv = NG_NODE_PRIVATE(node);
	struct mbuf *m;
	struct sscfu_arg arg;
	int error;

	if (uni_get_debug(priv->uni, UNI_FAC_SAAL) > 0)
		dump_saal_signal(node, sig, msg, 1);

	if (priv->lower == NULL) {
		if (msg != NULL)
			uni_msg_destroy(msg);
		return;
	}

	arg.sig = sig;

	m = uni_msg_pack_mbuf(msg, &arg, sizeof(arg));
	if (msg != NULL)
		uni_msg_destroy(msg);
	if (m == NULL)
		return;

	NG_SEND_DATA_ONLY(error, priv->lower, m);
}
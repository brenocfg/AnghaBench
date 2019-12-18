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
typedef  int /*<<< orphan*/  u_int32_t ;
struct uni_msg {int dummy; } ;
struct uni_arg {int sig; int /*<<< orphan*/  cookie; } ;
struct uni {int dummy; } ;
struct priv {int /*<<< orphan*/ * upper; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  enum uni_sig { ____Placeholder_uni_sig } uni_sig ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 struct mbuf* uni_msg_pack_mbuf (struct uni_msg*,struct uni_arg*,int) ; 

__attribute__((used)) static void
uni_uni_output(struct uni *uni, void *varg, enum uni_sig sig, u_int32_t cookie,
    struct uni_msg *msg)
{
	node_p node = (node_p)varg;
	struct priv *priv = NG_NODE_PRIVATE(node);
	struct mbuf *m;
	struct uni_arg arg;
	int error;

	if (priv->upper == NULL) {
		if (msg != NULL)
			uni_msg_destroy(msg);
		return;
	}
	arg.sig = sig;
	arg.cookie = cookie;

	m = uni_msg_pack_mbuf(msg, &arg, sizeof(arg));
	if (msg != NULL)
		uni_msg_destroy(msg);
	if (m == NULL)
		return;

	NG_SEND_DATA_ONLY(error, priv->upper, m);
}
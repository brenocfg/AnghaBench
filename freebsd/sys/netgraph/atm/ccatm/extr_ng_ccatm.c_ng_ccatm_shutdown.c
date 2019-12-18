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
struct ccnode {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  M_NG_CCATM ; 
 struct ccnode* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ccnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ccatm_shutdown(node_p node)
{
	struct ccnode *priv = NG_NODE_PRIVATE(node);

	cc_destroy(priv->data);

	free(priv, M_NG_CCATM);
	NG_NODE_SET_PRIVATE(node, NULL);

	NG_NODE_UNREF(node);

	return (0);
}
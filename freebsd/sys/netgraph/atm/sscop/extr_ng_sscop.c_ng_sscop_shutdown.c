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
struct priv {int /*<<< orphan*/  sscop; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  M_NG_SSCOP ; 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_sscop_shutdown(node_p node)
{
	struct priv *priv = NG_NODE_PRIVATE(node);

	sscop_destroy(priv->sscop);

	free(priv, M_NG_SSCOP);
	NG_NODE_SET_PRIVATE(node, NULL);

	NG_NODE_UNREF(node);

	return (0);
}
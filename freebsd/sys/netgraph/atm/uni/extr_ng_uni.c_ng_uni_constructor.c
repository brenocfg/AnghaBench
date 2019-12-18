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
struct priv {int /*<<< orphan*/ * uni; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NG_UNI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_FORCE_WRITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,struct priv*) ; 
 int /*<<< orphan*/  free (struct priv*,int /*<<< orphan*/ ) ; 
 struct priv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uni_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uni_funcs ; 

__attribute__((used)) static int
ng_uni_constructor(node_p node)
{
	struct priv *priv;

	priv = malloc(sizeof(*priv), M_NG_UNI, M_WAITOK | M_ZERO);

	if ((priv->uni = uni_create(node, &uni_funcs)) == NULL) {
		free(priv, M_NG_UNI);
		return (ENOMEM);
	}

	NG_NODE_SET_PRIVATE(node, priv);
	NG_NODE_FORCE_WRITER(node);

	return (0);
}
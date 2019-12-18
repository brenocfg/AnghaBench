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
struct priv {int /*<<< orphan*/ * sscf; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NG_SSCFU ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,struct priv*) ; 
 int /*<<< orphan*/  free (struct priv*,int /*<<< orphan*/ ) ; 
 struct priv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sscfu_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscfu_funcs ; 

__attribute__((used)) static int
ng_sscfu_constructor(node_p node)
{
	struct priv *priv;

	priv = malloc(sizeof(*priv), M_NG_SSCFU, M_WAITOK | M_ZERO);

	if ((priv->sscf = sscfu_create(node, &sscfu_funcs)) == NULL) {
		free(priv, M_NG_SSCFU);
		return (ENOMEM);
	}

	NG_NODE_SET_PRIVATE(node, priv);

	return (0);
}
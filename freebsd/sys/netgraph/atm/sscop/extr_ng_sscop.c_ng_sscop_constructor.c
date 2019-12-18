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
struct priv {int /*<<< orphan*/ * sscop; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NG_SSCOP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_FORCE_WRITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,struct priv*) ; 
 int /*<<< orphan*/  free (struct priv*,int /*<<< orphan*/ ) ; 
 struct priv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sscop_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscop_funcs ; 

__attribute__((used)) static int
ng_sscop_constructor(node_p node)
{
	struct priv *p;

	p = malloc(sizeof(*p), M_NG_SSCOP, M_WAITOK | M_ZERO);

	if ((p->sscop = sscop_create(node, &sscop_funcs)) == NULL) {
		free(p, M_NG_SSCOP);
		return (ENOMEM);
	}
	NG_NODE_SET_PRIVATE(node, p);

	/* All data message received by the node are expected to change the
	 * node's state. Therefor we must ensure, that we have a writer lock. */
	NG_NODE_FORCE_WRITER(node);

	return (0);
}
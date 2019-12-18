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
struct ng_nat_rdr_lst {int /*<<< orphan*/  lib; int /*<<< orphan*/  redirhead; } ;
typedef  struct ng_nat_rdr_lst* priv_p ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int /*<<< orphan*/  LibAliasUninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 struct ng_nat_rdr_lst* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ng_nat_rdr_lst* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct ng_nat_rdr_lst* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_nat_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);

	/* Free redirects list. */
	while (!STAILQ_EMPTY(&priv->redirhead)) {
		struct ng_nat_rdr_lst *entry = STAILQ_FIRST(&priv->redirhead);
		STAILQ_REMOVE_HEAD(&priv->redirhead, entries);
		free(entry, M_NETGRAPH);
	}

	/* Final free. */
	LibAliasUninit(priv->lib);
	free(priv, M_NETGRAPH);

	return (0);
}
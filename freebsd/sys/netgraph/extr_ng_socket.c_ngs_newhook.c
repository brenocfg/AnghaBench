#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct ngsock {int hmask; int /*<<< orphan*/ * hash; } ;
struct hookpriv {int /*<<< orphan*/  hook; } ;
typedef  TYPE_1__* node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int nd_numhooks; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HASHINIT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hookpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_SOCK ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,struct hookpriv*) ; 
 struct ngsock* NG_NODE_PRIVATE (TYPE_1__*) ; 
 size_t hash32_str (char const*,int /*<<< orphan*/ ) ; 
 struct hookpriv* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ngs_rehash (TYPE_1__*) ; 

__attribute__((used)) static int
ngs_newhook(node_p node, hook_p hook, const char *name)
{
	struct ngsock *const priv = NG_NODE_PRIVATE(node);
	struct hookpriv *hp;
	uint32_t h;

	hp = malloc(sizeof(*hp), M_NETGRAPH_SOCK, M_NOWAIT);
	if (hp == NULL)
		return (ENOMEM);
	if (node->nd_numhooks * 2 > priv->hmask)
		ngs_rehash(node);
	hp->hook = hook;
	h = hash32_str(name, HASHINIT) & priv->hmask;
	LIST_INSERT_HEAD(&priv->hash[h], hp, next);
	NG_HOOK_SET_PRIVATE(hook, hp);

	return (0);
}
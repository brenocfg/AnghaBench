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
struct iter_priv {int /*<<< orphan*/  n; int /*<<< orphan*/  a; int /*<<< orphan*/  region; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_addrs (struct iter_priv*,struct config_file*) ; 
 int /*<<< orphan*/  read_names (struct iter_priv*,struct config_file*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 

int priv_apply_cfg(struct iter_priv* priv, struct config_file* cfg)
{
	/* empty the current contents */
	regional_free_all(priv->region);
	addr_tree_init(&priv->a);
	name_tree_init(&priv->n);

	/* read new contents */
	if(!read_addrs(priv, cfg))
		return 0;
	if(!read_names(priv, cfg))
		return 0;

	/* prepare for lookups */
	addr_tree_init_parents(&priv->a);
	name_tree_init_parents(&priv->n);
	return 1;
}
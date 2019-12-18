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

/* Variables and functions */
 int /*<<< orphan*/  addr_tree_init (int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  name_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  priv_delete (struct iter_priv*) ; 
 int /*<<< orphan*/  regional_create () ; 

struct iter_priv* priv_create(void)
{
	struct iter_priv* priv = (struct iter_priv*)calloc(1, sizeof(*priv));
	if(!priv)
		return NULL;
	priv->region = regional_create();
	if(!priv->region) {
		priv_delete(priv);
		return NULL;
	}
	addr_tree_init(&priv->a);
	name_tree_init(&priv->n);
	return priv;
}
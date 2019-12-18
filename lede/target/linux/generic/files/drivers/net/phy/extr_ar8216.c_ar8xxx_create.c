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
struct ar8xxx_priv {int /*<<< orphan*/  mib_work; int /*<<< orphan*/  mib_lock; int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_mib_work_func ; 
 struct ar8xxx_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ar8xxx_priv *
ar8xxx_create(void)
{
	struct ar8xxx_priv *priv;

	priv = kzalloc(sizeof(struct ar8xxx_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	mutex_init(&priv->reg_mutex);
	mutex_init(&priv->mib_lock);
	INIT_DELAYED_WORK(&priv->mib_work, ar8xxx_mib_work_func);

	return priv;
}
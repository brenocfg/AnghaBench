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
struct ipoib_dev_priv {int dummy; } ;
struct ipoib_ah {int /*<<< orphan*/  ah; int /*<<< orphan*/  ref; scalar_t__ last_send; struct ipoib_dev_priv* priv; } ;
struct ib_pd {int dummy; } ;
struct ib_ah_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_create_ah (struct ib_pd*,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipoib_ah*) ; 
 struct ipoib_ah* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

struct ipoib_ah *ipoib_create_ah(struct ipoib_dev_priv *priv,
				 struct ib_pd *pd, struct ib_ah_attr *attr)
{
	struct ipoib_ah *ah;

	ah = kmalloc(sizeof *ah, GFP_KERNEL);
	if (!ah)
		return NULL;

	ah->priv      = priv;
	ah->last_send = 0;
	kref_init(&ah->ref);

	ah->ah = ib_create_ah(pd, attr);
	if (IS_ERR(ah->ah)) {
		kfree(ah);
		ah = NULL;
	} else
		ipoib_dbg(priv, "Created ah %p\n", ah->ah);

	return ah;
}
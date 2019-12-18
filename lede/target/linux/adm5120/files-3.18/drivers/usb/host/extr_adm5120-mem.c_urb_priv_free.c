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
struct urb_priv {int td_cnt; int /*<<< orphan*/  pending; scalar_t__* td; } ;
struct admhcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct urb_priv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td_free (struct admhcd*,scalar_t__) ; 

__attribute__((used)) static void urb_priv_free(struct admhcd *ahcd, struct urb_priv *urb_priv)
{
	int i;

	for (i = 0; i < urb_priv->td_cnt; i++)
		if (urb_priv->td[i])
			td_free(ahcd, urb_priv->td[i]);

	list_del(&urb_priv->pending);
	kfree(urb_priv);
}
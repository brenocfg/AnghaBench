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
struct fe_priv {int dummy; } ;

/* Variables and functions */
 int fe_alloc_rx (struct fe_priv*) ; 
 int fe_alloc_tx (struct fe_priv*) ; 

__attribute__((used)) static int fe_init_dma(struct fe_priv *priv)
{
	int err;

	err = fe_alloc_tx(priv);
	if (err)
		return err;

	err = fe_alloc_rx(priv);
	if (err)
		return err;

	return 0;
}
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
typedef  scalar_t__ u8 ;
struct cm_id_private {scalar_t__ private_data_len; void* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void cm_set_private_data(struct cm_id_private *cm_id_priv,
				 void *private_data, u8 private_data_len)
{
	if (cm_id_priv->private_data && cm_id_priv->private_data_len)
		kfree(cm_id_priv->private_data);

	cm_id_priv->private_data = private_data;
	cm_id_priv->private_data_len = private_data_len;
}
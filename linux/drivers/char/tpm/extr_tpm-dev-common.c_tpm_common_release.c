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
struct file_priv {scalar_t__ response_length; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  user_read_timer; int /*<<< orphan*/  async_work; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_singleshot_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 

void tpm_common_release(struct file *file, struct file_priv *priv)
{
	flush_work(&priv->async_work);
	del_singleshot_timer_sync(&priv->user_read_timer);
	flush_work(&priv->timeout_work);
	file->private_data = NULL;
	priv->response_length = 0;
}
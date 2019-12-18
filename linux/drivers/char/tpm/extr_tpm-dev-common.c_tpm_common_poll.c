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
struct file_priv {int /*<<< orphan*/  buffer_mutex; scalar_t__ response_length; int /*<<< orphan*/  async_wait; } ;
struct file {struct file_priv* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__poll_t tpm_common_poll(struct file *file, poll_table *wait)
{
	struct file_priv *priv = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &priv->async_wait, wait);
	mutex_lock(&priv->buffer_mutex);

	/*
	 * The response_length indicates if there is still response
	 * (or part of it) to be consumed. Partial reads decrease it
	 * by the number of bytes read, and write resets it the zero.
	 */
	if (priv->response_length)
		mask = EPOLLIN | EPOLLRDNORM;
	else
		mask = EPOLLOUT | EPOLLWRNORM;

	mutex_unlock(&priv->buffer_mutex);
	return mask;
}
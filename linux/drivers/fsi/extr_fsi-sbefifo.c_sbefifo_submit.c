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
struct sbefifo {scalar_t__ magic; int /*<<< orphan*/  lock; } ;
struct kvec {size_t iov_len; int /*<<< orphan*/ * iov_base; } ;
struct iov_iter {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ SBEFIFO_MAGIC ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE ; 
 int __sbefifo_submit (struct sbefifo*,int /*<<< orphan*/  const*,size_t,struct iov_iter*) ; 
 struct sbefifo* dev_get_drvdata (struct device*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int sbefifo_submit(struct device *dev, const __be32 *command, size_t cmd_len,
		   __be32 *response, size_t *resp_len)
{
	struct sbefifo *sbefifo;
        struct iov_iter resp_iter;
        struct kvec resp_iov;
	size_t rbytes;
	int rc;

	if (!dev)
		return -ENODEV;
	sbefifo = dev_get_drvdata(dev);
	if (!sbefifo)
		return -ENODEV;
	if (WARN_ON_ONCE(sbefifo->magic != SBEFIFO_MAGIC))
		return -ENODEV;
	if (!resp_len || !command || !response)
		return -EINVAL;

	/* Prepare iov iterator */
	rbytes = (*resp_len) * sizeof(__be32);
	resp_iov.iov_base = response;
	resp_iov.iov_len = rbytes;
        iov_iter_kvec(&resp_iter, WRITE, &resp_iov, 1, rbytes);

	/* Perform the command */
	mutex_lock(&sbefifo->lock);
	rc = __sbefifo_submit(sbefifo, command, cmd_len, &resp_iter);
	mutex_unlock(&sbefifo->lock);

	/* Extract the response length */
	rbytes -= iov_iter_count(&resp_iter);
	*resp_len = rbytes / sizeof(__be32);

	return rc;
}
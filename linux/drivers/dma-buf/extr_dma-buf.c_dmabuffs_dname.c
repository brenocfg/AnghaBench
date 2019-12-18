#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dma_buf {int /*<<< orphan*/  lock; scalar_t__ name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct dma_buf* d_fsdata; } ;

/* Variables and functions */
 int DMA_BUF_NAME_LEN ; 
 char* dynamic_dname (struct dentry*,char*,int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t strlcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static char *dmabuffs_dname(struct dentry *dentry, char *buffer, int buflen)
{
	struct dma_buf *dmabuf;
	char name[DMA_BUF_NAME_LEN];
	size_t ret = 0;

	dmabuf = dentry->d_fsdata;
	mutex_lock(&dmabuf->lock);
	if (dmabuf->name)
		ret = strlcpy(name, dmabuf->name, DMA_BUF_NAME_LEN);
	mutex_unlock(&dmabuf->lock);

	return dynamic_dname(dentry, buffer, buflen, "/%s:%s",
			     dentry->d_name.name, ret > 0 ? name : "");
}
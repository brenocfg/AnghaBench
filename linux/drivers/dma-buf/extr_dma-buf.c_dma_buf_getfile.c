#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct inode {int f_flags; TYPE_2__ f_path; struct dma_buf* private_data; int /*<<< orphan*/  i_size; } ;
struct file {int f_flags; TYPE_2__ f_path; struct dma_buf* private_data; int /*<<< orphan*/  i_size; } ;
struct dma_buf {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  mnt_sb; } ;
struct TYPE_5__ {struct dma_buf* d_fsdata; } ;

/* Variables and functions */
 struct inode* ERR_CAST (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int O_ACCMODE ; 
 int O_NONBLOCK ; 
 struct inode* alloc_anon_inode (int /*<<< orphan*/ ) ; 
 struct inode* alloc_file_pseudo (struct inode*,TYPE_3__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_buf_fops ; 
 TYPE_3__* dma_buf_mnt ; 
 int /*<<< orphan*/  inode_set_bytes (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct file *dma_buf_getfile(struct dma_buf *dmabuf, int flags)
{
	struct file *file;
	struct inode *inode = alloc_anon_inode(dma_buf_mnt->mnt_sb);

	if (IS_ERR(inode))
		return ERR_CAST(inode);

	inode->i_size = dmabuf->size;
	inode_set_bytes(inode, dmabuf->size);

	file = alloc_file_pseudo(inode, dma_buf_mnt, "dmabuf",
				 flags, &dma_buf_fops);
	if (IS_ERR(file))
		goto err_alloc_file;
	file->f_flags = flags & (O_ACCMODE | O_NONBLOCK);
	file->private_data = dmabuf;
	file->f_path.dentry->d_fsdata = dmabuf;

	return file;

err_alloc_file:
	iput(inode);
	return file;
}
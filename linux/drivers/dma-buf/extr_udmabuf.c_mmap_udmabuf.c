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
struct vm_area_struct {int vm_flags; struct udmabuf* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct udmabuf {int dummy; } ;
struct dma_buf {struct udmabuf* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_MAYSHARE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  udmabuf_vm_ops ; 

__attribute__((used)) static int mmap_udmabuf(struct dma_buf *buf, struct vm_area_struct *vma)
{
	struct udmabuf *ubuf = buf->priv;

	if ((vma->vm_flags & (VM_SHARED | VM_MAYSHARE)) == 0)
		return -EINVAL;

	vma->vm_ops = &udmabuf_vm_ops;
	vma->vm_private_data = ubuf;
	return 0;
}
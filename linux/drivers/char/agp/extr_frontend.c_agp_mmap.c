#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned int vm_end; unsigned int vm_start; unsigned long vm_pgoff; long vm_ops; int /*<<< orphan*/  vm_page_prot; } ;
struct file {struct agp_file_private* private_data; } ;
struct agp_kern_info {unsigned int aper_size; long vm_ops; unsigned long aper_base; } ;
struct agp_file_private {int /*<<< orphan*/  access_flags; } ;
struct agp_client {int dummy; } ;
struct TYPE_4__ {int backend_acquired; int /*<<< orphan*/  agp_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FF_IS_CLIENT ; 
 int /*<<< orphan*/  AGP_FF_IS_CONTROLLER ; 
 int /*<<< orphan*/  AGP_FF_IS_VALID ; 
 int /*<<< orphan*/  DBG (char*,long,...) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EPERM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  agp_bridge ; 
 int /*<<< orphan*/  agp_copy_info (int /*<<< orphan*/ ,struct agp_kern_info*) ; 
 TYPE_2__ agp_fe ; 
 struct agp_client* agp_find_client_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_find_seg_in_client (struct agp_client*,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,unsigned int,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int agp_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned int size, current_size;
	unsigned long offset;
	struct agp_client *client;
	struct agp_file_private *priv = file->private_data;
	struct agp_kern_info kerninfo;

	mutex_lock(&(agp_fe.agp_mutex));

	if (agp_fe.backend_acquired != true)
		goto out_eperm;

	if (!(test_bit(AGP_FF_IS_VALID, &priv->access_flags)))
		goto out_eperm;

	agp_copy_info(agp_bridge, &kerninfo);
	size = vma->vm_end - vma->vm_start;
	current_size = kerninfo.aper_size;
	current_size = current_size * 0x100000;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	DBG("%lx:%lx", offset, offset+size);

	if (test_bit(AGP_FF_IS_CLIENT, &priv->access_flags)) {
		if ((size + offset) > current_size)
			goto out_inval;

		client = agp_find_client_by_pid(current->pid);

		if (client == NULL)
			goto out_eperm;

		if (!agp_find_seg_in_client(client, offset, size, vma->vm_page_prot))
			goto out_inval;

		DBG("client vm_ops=%p", kerninfo.vm_ops);
		if (kerninfo.vm_ops) {
			vma->vm_ops = kerninfo.vm_ops;
		} else if (io_remap_pfn_range(vma, vma->vm_start,
				(kerninfo.aper_base + offset) >> PAGE_SHIFT,
				size,
				pgprot_writecombine(vma->vm_page_prot))) {
			goto out_again;
		}
		mutex_unlock(&(agp_fe.agp_mutex));
		return 0;
	}

	if (test_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags)) {
		if (size != current_size)
			goto out_inval;

		DBG("controller vm_ops=%p", kerninfo.vm_ops);
		if (kerninfo.vm_ops) {
			vma->vm_ops = kerninfo.vm_ops;
		} else if (io_remap_pfn_range(vma, vma->vm_start,
				kerninfo.aper_base >> PAGE_SHIFT,
				size,
				pgprot_writecombine(vma->vm_page_prot))) {
			goto out_again;
		}
		mutex_unlock(&(agp_fe.agp_mutex));
		return 0;
	}

out_eperm:
	mutex_unlock(&(agp_fe.agp_mutex));
	return -EPERM;

out_inval:
	mutex_unlock(&(agp_fe.agp_mutex));
	return -EINVAL;

out_again:
	mutex_unlock(&(agp_fe.agp_mutex));
	return -EAGAIN;
}
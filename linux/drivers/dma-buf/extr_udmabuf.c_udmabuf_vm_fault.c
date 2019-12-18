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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {size_t pgoff; int /*<<< orphan*/  page; struct vm_area_struct* vma; } ;
struct vm_area_struct {struct udmabuf* vm_private_data; } ;
struct udmabuf {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t udmabuf_vm_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct udmabuf *ubuf = vma->vm_private_data;

	vmf->page = ubuf->pages[vmf->pgoff];
	get_page(vmf->page);
	return 0;
}
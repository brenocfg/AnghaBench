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
struct vm_area_struct {unsigned long vm_start; int /*<<< orphan*/  vm_end; scalar_t__ vm_file; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int ARC_PATH_MAX ; 
 scalar_t__ IS_ERR (char*) ; 
 unsigned long TASK_UNMAPPED_BASE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 char* file_path (scalar_t__,char*,int) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_faulting_vma(unsigned long address)
{
	struct vm_area_struct *vma;
	struct mm_struct *active_mm = current->active_mm;

	/* can't use print_vma_addr() yet as it doesn't check for
	 * non-inclusive vma
	 */
	down_read(&active_mm->mmap_sem);
	vma = find_vma(active_mm, address);

	/* check against the find_vma( ) behaviour which returns the next VMA
	 * if the container VMA is not found
	 */
	if (vma && (vma->vm_start <= address)) {
		char buf[ARC_PATH_MAX];
		char *nm = "?";

		if (vma->vm_file) {
			nm = file_path(vma->vm_file, buf, ARC_PATH_MAX-1);
			if (IS_ERR(nm))
				nm = "?";
		}
		pr_info("    @off 0x%lx in [%s]\n"
			"    VMA: 0x%08lx to 0x%08lx\n",
			vma->vm_start < TASK_UNMAPPED_BASE ?
				address : address - vma->vm_start,
			nm, vma->vm_start, vma->vm_end);
	} else
		pr_info("    @No matching VMA found\n");

	up_read(&active_mm->mmap_sem);
}
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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfag12864b_buffer ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 int vm_map_pages_zero (struct vm_area_struct*,struct page**,int) ; 

__attribute__((used)) static int cfag12864bfb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct page *pages = virt_to_page(cfag12864b_buffer);

	return vm_map_pages_zero(vma, &pages, 1);
}
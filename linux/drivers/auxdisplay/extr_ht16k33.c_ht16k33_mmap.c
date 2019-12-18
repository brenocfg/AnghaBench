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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
struct ht16k33_priv {TYPE_1__ fbdev; } ;
struct fb_info {struct ht16k33_priv* par; } ;

/* Variables and functions */
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 int vm_map_pages_zero (struct vm_area_struct*,struct page**,int) ; 

__attribute__((used)) static int ht16k33_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct ht16k33_priv *priv = info->par;
	struct page *pages = virt_to_page(priv->fbdev.buffer);

	return vm_map_pages_zero(vma, &pages, 1);
}
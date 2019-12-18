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
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
struct mlx4_buf {int nbufs; TYPE_2__ direct; TYPE_1__* page_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc (int,int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_en_map_buffer(struct mlx4_buf *buf)
{
	struct page **pages;
	int i;

        // if nbufs == 1 - there is no need to vmap 
        // if buf->direct.buf is not NULL it means that vmap was already done by mlx4_alloc_buff
	if (buf->direct.buf != NULL || buf->nbufs == 1)
		return 0;

	pages = kmalloc(sizeof *pages * buf->nbufs, GFP_KERNEL);
	if (!pages)
		return -ENOMEM;

	for (i = 0; i < buf->nbufs; ++i)
		pages[i] = virt_to_page(buf->page_list[i].buf);

	buf->direct.buf = vmap(pages, buf->nbufs, VM_MAP, PAGE_KERNEL);
	kfree(pages);
	if (!buf->direct.buf)
		return -ENOMEM;

	return 0;
}
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
struct udmabuf {struct page** pages; } ;
struct page {int dummy; } ;
struct dma_buf {struct udmabuf* priv; } ;

/* Variables and functions */
 void* kmap (struct page*) ; 

__attribute__((used)) static void *kmap_udmabuf(struct dma_buf *buf, unsigned long page_num)
{
	struct udmabuf *ubuf = buf->priv;
	struct page *page = ubuf->pages[page_num];

	return kmap(page);
}
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
struct udmabuf {size_t pagecount; struct udmabuf* pages; } ;
struct dma_buf {struct udmabuf* priv; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct udmabuf*) ; 
 int /*<<< orphan*/  put_page (struct udmabuf) ; 

__attribute__((used)) static void release_udmabuf(struct dma_buf *buf)
{
	struct udmabuf *ubuf = buf->priv;
	pgoff_t pg;

	for (pg = 0; pg < ubuf->pagecount; pg++)
		put_page(ubuf->pages[pg]);
	kfree(ubuf->pages);
	kfree(ubuf);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct buffer_desc {int /*<<< orphan*/  dir; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  phys_next; struct buffer_desc* next; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_pool ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct buffer_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_buf_chain(struct device *dev, struct buffer_desc *buf,
			   dma_addr_t phys)
{
	while (buf) {
		struct buffer_desc *buf1;
		u32 phys1;

		buf1 = buf->next;
		phys1 = buf->phys_next;
		dma_unmap_single(dev, buf->phys_next, buf->buf_len, buf->dir);
		dma_pool_free(buffer_pool, buf, phys);
		buf = buf1;
		phys = phys1;
	}
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_dbg (char*) ; 

u8 *zip_data_buf_alloc(u64 size)
{
	u8 *ptr;

	ptr = (u8 *)__get_free_pages((GFP_KERNEL | GFP_DMA),
					get_order(size));

	if (!ptr)
		return NULL;

	memset(ptr, 0, size);

	zip_dbg("Data buffer allocation success\n");
	return ptr;
}
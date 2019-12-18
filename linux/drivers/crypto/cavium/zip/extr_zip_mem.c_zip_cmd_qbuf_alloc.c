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
typedef  int /*<<< orphan*/  u64 ;
struct zip_device {TYPE_1__* iq; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sw_head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  ZIP_CMD_QBUF_SIZE ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_dbg (char*,int,int /*<<< orphan*/ *) ; 

int zip_cmd_qbuf_alloc(struct zip_device *zip, int q)
{
	zip->iq[q].sw_head = (u64 *)__get_free_pages((GFP_KERNEL | GFP_DMA),
						get_order(ZIP_CMD_QBUF_SIZE));

	if (!zip->iq[q].sw_head)
		return -ENOMEM;

	memset(zip->iq[q].sw_head, 0, ZIP_CMD_QBUF_SIZE);

	zip_dbg("cmd_qbuf_alloc[%d] Success : %p\n", q, zip->iq[q].sw_head);
	return 0;
}
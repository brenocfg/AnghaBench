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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct ecore_ilt_client_cfg {TYPE_1__ p_size; } ;
struct ecore_ilt_cli_blk {int total_size; int real_size_in_page; int start_line; } ;

/* Variables and functions */
 int ILT_PAGE_IN_BYTES (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ilt_cli_blk_fill(struct ecore_ilt_client_cfg	*p_cli,
				   struct ecore_ilt_cli_blk	*p_blk,
				   u32				start_line,
				   u32				total_size,
				   u32				elem_size)
{
	u32 ilt_size = ILT_PAGE_IN_BYTES(p_cli->p_size.val);

	/* verify that it's called once for each block */
	if (p_blk->total_size)
		return;

	p_blk->total_size = total_size;
	p_blk->real_size_in_page = 0;
	if (elem_size)
		p_blk->real_size_in_page = (ilt_size / elem_size) * elem_size;
	p_blk->start_line = start_line;
}
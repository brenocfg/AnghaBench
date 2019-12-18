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

/* Variables and functions */
 scalar_t__ MLX5_CMD_OP_MANAGE_PAGES ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_in ; 
 int /*<<< orphan*/  opcode ; 

__attribute__((used)) static int is_manage_pages(void *in)
{
	return MLX5_GET(mbox_in, in, opcode) == MLX5_CMD_OP_MANAGE_PAGES;
}
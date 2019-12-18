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
struct ibv_mw {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_dealloc_mw {scalar_t__ reserved; int /*<<< orphan*/  mw_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEALLOC_MW ; 
 int /*<<< orphan*/  IBV_INIT_CMD (struct ibv_dealloc_mw*,size_t,int /*<<< orphan*/ ) ; 
 int errno ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_dealloc_mw*,size_t) ; 

int ibv_cmd_dealloc_mw(struct ibv_mw *mw,
		       struct ibv_dealloc_mw *cmd, size_t cmd_size)
{
	IBV_INIT_CMD(cmd, cmd_size, DEALLOC_MW);
	cmd->mw_handle = mw->handle;
	cmd->reserved = 0;

	if (write(mw->context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	return 0;
}
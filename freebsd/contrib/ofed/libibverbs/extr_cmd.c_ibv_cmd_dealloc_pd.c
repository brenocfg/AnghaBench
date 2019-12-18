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
struct ibv_pd {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_dealloc_pd {int /*<<< orphan*/  pd_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEALLOC_PD ; 
 int /*<<< orphan*/  IBV_INIT_CMD (struct ibv_dealloc_pd*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int write (int /*<<< orphan*/ ,struct ibv_dealloc_pd*,int) ; 

int ibv_cmd_dealloc_pd(struct ibv_pd *pd)
{
	struct ibv_dealloc_pd cmd;

	IBV_INIT_CMD(&cmd, sizeof cmd, DEALLOC_PD);
	cmd.pd_handle = pd->handle;

	if (write(pd->context->cmd_fd, &cmd, sizeof cmd) != sizeof cmd)
		return errno;

	return 0;
}
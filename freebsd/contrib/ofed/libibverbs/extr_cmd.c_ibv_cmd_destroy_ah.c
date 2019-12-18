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
struct ibv_destroy_ah {int /*<<< orphan*/  ah_handle; } ;
struct ibv_ah {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_AH ; 
 int /*<<< orphan*/  IBV_INIT_CMD (struct ibv_destroy_ah*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int write (int /*<<< orphan*/ ,struct ibv_destroy_ah*,int) ; 

int ibv_cmd_destroy_ah(struct ibv_ah *ah)
{
	struct ibv_destroy_ah cmd;

	IBV_INIT_CMD(&cmd, sizeof cmd, DESTROY_AH);
	cmd.ah_handle = ah->handle;

	if (write(ah->context->cmd_fd, &cmd, sizeof cmd) != sizeof cmd)
		return errno;

	return 0;
}
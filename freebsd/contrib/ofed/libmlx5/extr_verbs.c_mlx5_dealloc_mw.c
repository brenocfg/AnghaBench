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
struct ibv_mw {int dummy; } ;
struct ibv_dealloc_mw {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_mw*) ; 
 int ibv_cmd_dealloc_mw (struct ibv_mw*,struct ibv_dealloc_mw*,int) ; 

int mlx5_dealloc_mw(struct ibv_mw *mw)
{
	int ret;
	struct ibv_dealloc_mw cmd;

	ret = ibv_cmd_dealloc_mw(mw, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	free(mw);
	return 0;
}
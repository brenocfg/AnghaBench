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
struct mlx5_cmd_work_ent {int /*<<< orphan*/  cb_timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_cmd_work_ent*) ; 

__attribute__((used)) static void free_cmd(struct mlx5_cmd_work_ent *ent)
{
        cancel_delayed_work_sync(&ent->cb_timeout_work);
	kfree(ent);
}
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
struct bcom_task {int num_bd; int bd_size; int /*<<< orphan*/  tasknum; scalar_t__ outdex; scalar_t__ index; int /*<<< orphan*/  bd; } ;
struct bcom_ata_var {int /*<<< orphan*/  bd_base; int /*<<< orphan*/  bd_start; } ;

/* Variables and functions */
 scalar_t__ bcom_task_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

void bcom_ata_reset_bd(struct bcom_task *tsk)
{
	struct bcom_ata_var *var;

	/* Reset all BD */
	memset(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	tsk->index = 0;
	tsk->outdex = 0;

	var = (struct bcom_ata_var *) bcom_task_var(tsk->tasknum);
	var->bd_start = var->bd_base;
}
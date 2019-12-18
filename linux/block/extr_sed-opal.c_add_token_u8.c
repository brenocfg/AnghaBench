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
struct opal_dev {int /*<<< orphan*/  pos; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_add (int*,struct opal_dev*,int) ; 

__attribute__((used)) static void add_token_u8(int *err, struct opal_dev *cmd, u8 tok)
{
	if (!can_add(err, cmd, 1))
		return;

	cmd->cmd[cmd->pos++] = tok;
}
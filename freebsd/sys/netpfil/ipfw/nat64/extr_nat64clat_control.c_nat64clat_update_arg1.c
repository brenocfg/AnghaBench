#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  arg1; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */

__attribute__((used)) static void
nat64clat_update_arg1(ipfw_insn *cmd, uint16_t idx)
{

	cmd->arg1 = idx;
}
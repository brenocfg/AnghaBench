#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_4__ {TYPE_1__ p; } ;
typedef  TYPE_2__ ipfw_insn_if ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */

__attribute__((used)) static void
update_via(ipfw_insn *cmd, uint16_t idx)
{
	ipfw_insn_if *cmdif;

	cmdif = (ipfw_insn_if *)cmd;
	cmdif->p.kidx = idx;
}
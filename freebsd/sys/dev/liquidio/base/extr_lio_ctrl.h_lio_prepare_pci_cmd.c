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
typedef  union lio_instr_64B {int dummy; } lio_instr_64B ;
typedef  union lio_cmd_setup {int dummy; } lio_cmd_setup ;
typedef  int /*<<< orphan*/  uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_prepare_pci_cmd_o3 (struct octeon_device*,union lio_instr_64B*,union lio_cmd_setup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lio_prepare_pci_cmd(struct octeon_device *oct, union lio_instr_64B *cmd,
		    union lio_cmd_setup *setup, uint32_t tag)
{

	lio_prepare_pci_cmd_o3(oct, cmd, setup, tag);
}
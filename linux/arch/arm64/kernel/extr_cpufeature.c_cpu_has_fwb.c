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
typedef  int u64 ;
struct arm64_cpu_capabilities {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CLIDR_EL1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int read_sysreg_s (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_has_fwb(const struct arm64_cpu_capabilities *__unused)
{
	u64 val = read_sysreg_s(SYS_CLIDR_EL1);

	/* Check that CLIDR_EL1.LOU{U,IS} are both 0 */
	WARN_ON(val & (7 << 27 | 7 << 21));
}
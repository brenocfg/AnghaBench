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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 scalar_t__ CPU_PART (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_PART_THUNDERX ; 
 scalar_t__ CPU_PART_THUNDERX_81XX ; 
 int CPU_REV (int /*<<< orphan*/ ) ; 
 int CPU_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcast_tlbi_workaround ; 
 int /*<<< orphan*/  get_midr () ; 

__attribute__((used)) static void
install_thunderx_bcast_tlbi_workaround(void)
{
	u_int midr;

	midr = get_midr();
	if (CPU_PART(midr) == CPU_PART_THUNDERX_81XX)
		PCPU_SET(bcast_tlbi_workaround, 1);
	else if (CPU_PART(midr) == CPU_PART_THUNDERX) {
		if (CPU_VAR(midr) == 0) {
			/* ThunderX 1.x */
			PCPU_SET(bcast_tlbi_workaround, 1);
		} else if (CPU_VAR(midr) == 1 && CPU_REV(midr) <= 1) {
			/* ThunderX 2.0 - 2.1 */
			PCPU_SET(bcast_tlbi_workaround, 1);
		}
	}
}
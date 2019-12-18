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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  elink_e3b0_sp_get_pri_cli_reg (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static uint64_t elink_e3b0_sp_get_pri_cli_reg_pbf(const uint8_t cos, const uint8_t pri_set)
{
	const uint8_t pbf_cos_offset = 0;
	const uint8_t pbf_pri_offset = 0;

	return elink_e3b0_sp_get_pri_cli_reg(cos, pbf_cos_offset, pri_set,
		pbf_pri_offset, 3);

}
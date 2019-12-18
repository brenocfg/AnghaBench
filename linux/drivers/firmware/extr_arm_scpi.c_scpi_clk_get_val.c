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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  rate ;
typedef  int /*<<< orphan*/  le_clk_id ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_CLOCK_VALUE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scpi_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long scpi_clk_get_val(u16 clk_id)
{
	int ret;
	__le32 rate;
	__le16 le_clk_id = cpu_to_le16(clk_id);

	ret = scpi_send_message(CMD_GET_CLOCK_VALUE, &le_clk_id,
				sizeof(le_clk_id), &rate, sizeof(rate));

	return ret ? ret : le32_to_cpu(rate);
}
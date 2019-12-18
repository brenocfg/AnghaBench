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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  pstate ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_DEVICE_PWR_STATE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int scpi_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static int scpi_device_get_power_state(u16 dev_id)
{
	int ret;
	u8 pstate;
	__le16 id = cpu_to_le16(dev_id);

	ret = scpi_send_message(CMD_GET_DEVICE_PWR_STATE, &id,
				sizeof(id), &pstate, sizeof(pstate));
	return ret ? ret : pstate;
}
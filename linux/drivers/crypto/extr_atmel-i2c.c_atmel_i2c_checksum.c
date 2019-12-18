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
struct atmel_i2c_cmd {int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_SIZE ; 
 int /*<<< orphan*/  bitrev16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void atmel_i2c_checksum(struct atmel_i2c_cmd *cmd)
{
	u8 *data = &cmd->count;
	size_t len = cmd->count - CRC_SIZE;
	__le16 *__crc16 = (__le16 *)(data + len);

	*__crc16 = cpu_to_le16(bitrev16(crc16(0, data, len)));
}
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
typedef  int u32 ;
typedef  int /*<<< orphan*/  data_to_crc ;

/* Variables and functions */
 int const CDU_CONTEXT_VALIDATION_CFG_USE_ACTIVE ; 
 int const CDU_CONTEXT_VALIDATION_CFG_USE_CID ; 
 int const CDU_CONTEXT_VALIDATION_CFG_USE_REGION ; 
 int const CDU_CONTEXT_VALIDATION_CFG_USE_TYPE ; 
 int const CDU_CONTEXT_VALIDATION_CFG_VALIDATION_TYPE_SHIFT ; 
 int CDU_VALIDATION_DEFAULT_CFG ; 
 int /*<<< orphan*/  CRC8_INIT_VALUE ; 
 int OSAL_BE32_TO_CPU (int) ; 
 int OSAL_CRC8 (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_CRC8_POPULATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdu_crc8_table ; 

__attribute__((used)) static u8 ecore_calc_cdu_validation_byte(u8 conn_type, u8 region, u32 cid)
{
	const u8 validation_cfg = CDU_VALIDATION_DEFAULT_CFG;

	static u8 crc8_table_valid;	/*automatically initialized to 0*/
	u8 crc, validation_byte = 0;
	u32 validation_string = 0;
	u32 data_to_crc;

	if (crc8_table_valid == 0) {
		OSAL_CRC8_POPULATE(cdu_crc8_table, 0x07);
		crc8_table_valid = 1;
	}

	/* The CRC is calculated on the String-to-compress:
	 * [31:8]  = {CID[31:20],CID[11:0]}
	 * [7:4]   = Region
	 * [3:0]   = Type
	 */
	if ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_CID) & 1)
		validation_string |= (cid & 0xFFF00000) | ((cid & 0xFFF) << 8);

	if ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_REGION) & 1)
		validation_string |= ((region & 0xF) << 4);

	if ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_TYPE) & 1)
		validation_string |= (conn_type & 0xF);

	/* Convert to big-endian and calculate CRC8*/
	data_to_crc = OSAL_BE32_TO_CPU(validation_string);

	crc = OSAL_CRC8(cdu_crc8_table, (u8 *)&data_to_crc, sizeof(data_to_crc), CRC8_INIT_VALUE);

	/* The validation byte [7:0] is composed:
	 * for type A validation
	 * [7]		= active configuration bit
	 * [6:0]	= crc[6:0]
	 *
	 * for type B validation
	 * [7]		= active configuration bit
	 * [6:3]	= connection_type[3:0]
	 * [2:0]	= crc[2:0]
	 */
	validation_byte |= ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_ACTIVE) & 1) << 7;

	if ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_VALIDATION_TYPE_SHIFT) & 1)
		validation_byte |= ((conn_type & 0xF) << 3) | (crc & 0x7);
	else
		validation_byte |= crc & 0x7F;

	return validation_byte;
}
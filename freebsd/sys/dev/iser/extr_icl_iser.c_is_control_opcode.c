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
typedef  int uint8_t ;

/* Variables and functions */
#define  ISCSI_BHS_OPCODE_LOGIN_REQUEST 132 
#define  ISCSI_BHS_OPCODE_LOGOUT_REQUEST 131 
#define  ISCSI_BHS_OPCODE_NOP_OUT 130 
#define  ISCSI_BHS_OPCODE_SCSI_COMMAND 129 
#define  ISCSI_BHS_OPCODE_TEXT_REQUEST 128 
 int ISCSI_OPCODE_MASK ; 
 int /*<<< orphan*/  ISER_ERR (char*,int) ; 

__attribute__((used)) static bool
is_control_opcode(uint8_t opcode)
{
	bool is_control = false;

	switch (opcode & ISCSI_OPCODE_MASK) {
		case ISCSI_BHS_OPCODE_NOP_OUT:
		case ISCSI_BHS_OPCODE_LOGIN_REQUEST:
		case ISCSI_BHS_OPCODE_LOGOUT_REQUEST:
		case ISCSI_BHS_OPCODE_TEXT_REQUEST:
			is_control = true;
			break;
		case ISCSI_BHS_OPCODE_SCSI_COMMAND:
			is_control = false;
			break;
		default:
			ISER_ERR("unknown opcode %d", opcode);
	}

	return (is_control);
}
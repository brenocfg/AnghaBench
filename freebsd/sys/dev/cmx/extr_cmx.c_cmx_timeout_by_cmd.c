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
 unsigned long CCID_DRIVER_ASYNC_POWERUP_TIMEOUT ; 
 unsigned long CCID_DRIVER_BULK_DEFAULT_TIMEOUT ; 
 unsigned long CCID_DRIVER_MINIMUM_TIMEOUT ; 
#define  CMD_PC_TO_RDR_ESCAPE 139 
#define  CMD_PC_TO_RDR_GETPARAMETERS 138 
#define  CMD_PC_TO_RDR_GETSLOTSTATUS 137 
#define  CMD_PC_TO_RDR_ICCCLOCK 136 
#define  CMD_PC_TO_RDR_ICCPOWEROFF 135 
#define  CMD_PC_TO_RDR_ICCPOWERON 134 
#define  CMD_PC_TO_RDR_OK_SECURE 133 
#define  CMD_PC_TO_RDR_RESETPARAMETERS 132 
#define  CMD_PC_TO_RDR_SECURE 131 
#define  CMD_PC_TO_RDR_SETPARAMETERS 130 
#define  CMD_PC_TO_RDR_TEST_SECURE 129 
#define  CMD_PC_TO_RDR_XFRBLOCK 128 

__attribute__((used)) static inline unsigned long
cmx_timeout_by_cmd(uint8_t cmd)
{
	switch (cmd) {
	case CMD_PC_TO_RDR_XFRBLOCK:
	case CMD_PC_TO_RDR_SECURE:
	case CMD_PC_TO_RDR_TEST_SECURE:
	case CMD_PC_TO_RDR_OK_SECURE:
		return CCID_DRIVER_BULK_DEFAULT_TIMEOUT;

	case CMD_PC_TO_RDR_ICCPOWERON:
		return CCID_DRIVER_ASYNC_POWERUP_TIMEOUT;

	case CMD_PC_TO_RDR_GETSLOTSTATUS:
	case CMD_PC_TO_RDR_ICCPOWEROFF:
	case CMD_PC_TO_RDR_GETPARAMETERS:
	case CMD_PC_TO_RDR_RESETPARAMETERS:
	case CMD_PC_TO_RDR_SETPARAMETERS:
	case CMD_PC_TO_RDR_ESCAPE:
	case CMD_PC_TO_RDR_ICCCLOCK:
	default:
		return CCID_DRIVER_MINIMUM_TIMEOUT;
	}
}
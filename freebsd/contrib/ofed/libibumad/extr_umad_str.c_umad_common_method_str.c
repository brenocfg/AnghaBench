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
#define  UMAD_METHOD_GET 135 
#define  UMAD_METHOD_GET_RESP 134 
#define  UMAD_METHOD_REPORT 133 
#define  UMAD_METHOD_REPORT_RESP 132 
#define  UMAD_METHOD_SEND 131 
#define  UMAD_METHOD_SET 130 
#define  UMAD_METHOD_TRAP 129 
#define  UMAD_METHOD_TRAP_REPRESS 128 

__attribute__((used)) static const char * umad_common_method_str(uint8_t method)
{
	switch(method) {
		case UMAD_METHOD_GET:
			return ("Get");
		case UMAD_METHOD_SET:
			return ("Set");
		case UMAD_METHOD_GET_RESP:
			return ("GetResp");
		case UMAD_METHOD_SEND:
			return ("Send");
		case UMAD_METHOD_TRAP:
			return ("Trap");
		case UMAD_METHOD_REPORT:
			return ("Report");
		case UMAD_METHOD_REPORT_RESP:
			return ("ReportResp");
		case UMAD_METHOD_TRAP_REPRESS:
			return ("TrapRepress");
		default:
			return ("<unknown");
	}
}
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

/* Variables and functions */
#define  RADIUS_CODE_ACCESS_ACCEPT 142 
#define  RADIUS_CODE_ACCESS_CHALLENGE 141 
#define  RADIUS_CODE_ACCESS_REJECT 140 
#define  RADIUS_CODE_ACCESS_REQUEST 139 
#define  RADIUS_CODE_ACCOUNTING_REQUEST 138 
#define  RADIUS_CODE_ACCOUNTING_RESPONSE 137 
#define  RADIUS_CODE_COA_ACK 136 
#define  RADIUS_CODE_COA_NAK 135 
#define  RADIUS_CODE_COA_REQUEST 134 
#define  RADIUS_CODE_DISCONNECT_ACK 133 
#define  RADIUS_CODE_DISCONNECT_NAK 132 
#define  RADIUS_CODE_DISCONNECT_REQUEST 131 
#define  RADIUS_CODE_RESERVED 130 
#define  RADIUS_CODE_STATUS_CLIENT 129 
#define  RADIUS_CODE_STATUS_SERVER 128 

__attribute__((used)) static const char *radius_code_string(u8 code)
{
	switch (code) {
	case RADIUS_CODE_ACCESS_REQUEST: return "Access-Request";
	case RADIUS_CODE_ACCESS_ACCEPT: return "Access-Accept";
	case RADIUS_CODE_ACCESS_REJECT: return "Access-Reject";
	case RADIUS_CODE_ACCOUNTING_REQUEST: return "Accounting-Request";
	case RADIUS_CODE_ACCOUNTING_RESPONSE: return "Accounting-Response";
	case RADIUS_CODE_ACCESS_CHALLENGE: return "Access-Challenge";
	case RADIUS_CODE_STATUS_SERVER: return "Status-Server";
	case RADIUS_CODE_STATUS_CLIENT: return "Status-Client";
	case RADIUS_CODE_RESERVED: return "Reserved";
	case RADIUS_CODE_DISCONNECT_REQUEST: return "Disconnect-Request";
	case RADIUS_CODE_DISCONNECT_ACK: return "Disconnect-ACK";
	case RADIUS_CODE_DISCONNECT_NAK: return "Disconnect-NAK";
	case RADIUS_CODE_COA_REQUEST: return "CoA-Request";
	case RADIUS_CODE_COA_ACK: return "CoA-ACK";
	case RADIUS_CODE_COA_NAK: return "CoA-NAK";
	default: return "?Unknown?";
	}
}
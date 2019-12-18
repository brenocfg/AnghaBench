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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  UMAD_CM_ATTR_APR 140 
#define  UMAD_CM_ATTR_DREP 139 
#define  UMAD_CM_ATTR_DREQ 138 
#define  UMAD_CM_ATTR_LAP 137 
#define  UMAD_CM_ATTR_MRA 136 
#define  UMAD_CM_ATTR_REJ 135 
#define  UMAD_CM_ATTR_REP 134 
#define  UMAD_CM_ATTR_REQ 133 
#define  UMAD_CM_ATTR_RTU 132 
#define  UMAD_CM_ATTR_SAP 131 
#define  UMAD_CM_ATTR_SIDR_REP 130 
#define  UMAD_CM_ATTR_SIDR_REQ 129 
#define  UMAD_CM_ATTR_SPR 128 
 int be16toh (int /*<<< orphan*/ ) ; 
 char const* umad_common_attr_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * umad_cm_attr_str(__be16 attr_id)
{
	switch(be16toh(attr_id)) {
		case UMAD_CM_ATTR_REQ:
			return "ConnectRequest";
		case UMAD_CM_ATTR_MRA:
			return "MsgRcptAck";
		case UMAD_CM_ATTR_REJ:
			return "ConnectReject";
		case UMAD_CM_ATTR_REP:
			return "ConnectReply";
		case UMAD_CM_ATTR_RTU:
			return "ReadyToUse";
		case UMAD_CM_ATTR_DREQ:
			return "DisconnectRequest";
		case UMAD_CM_ATTR_DREP:
			return "DisconnectReply";
		case UMAD_CM_ATTR_SIDR_REQ:
			return "ServiceIDResReq";
		case UMAD_CM_ATTR_SIDR_REP:
			return "ServiceIDResReqResp";
		case UMAD_CM_ATTR_LAP:
			return "LoadAlternatePath";
		case UMAD_CM_ATTR_APR:
			return "AlternatePathResponse";
		case UMAD_CM_ATTR_SAP:
			return "SuggestAlternatePath";
		case UMAD_CM_ATTR_SPR:
			return "SuggestPathResponse";
		default:
			return (umad_common_attr_str(attr_id));
	}
	return ("<unknown>");
}
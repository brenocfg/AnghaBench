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
#define  UMAD_SA_METHOD_DELETE 134 
#define  UMAD_SA_METHOD_DELETE_RESP 133 
#define  UMAD_SA_METHOD_GET_MULTI 132 
#define  UMAD_SA_METHOD_GET_MULTI_RESP 131 
#define  UMAD_SA_METHOD_GET_TABLE 130 
#define  UMAD_SA_METHOD_GET_TABLE_RESP 129 
#define  UMAD_SA_METHOD_GET_TRACE_TABLE 128 
 char const* umad_common_method_str (int) ; 

__attribute__((used)) static const char * umad_sa_method_str(uint8_t method)
{
	switch(method) {
		case UMAD_SA_METHOD_GET_TABLE:
			return ("GetTable");
		case UMAD_SA_METHOD_GET_TABLE_RESP:
			return ("GetTableResp");
		case UMAD_SA_METHOD_DELETE:
			return ("Delete");
		case UMAD_SA_METHOD_DELETE_RESP:
			return ("DeleteResp");
		case UMAD_SA_METHOD_GET_MULTI:
			return ("GetMulti");
		case UMAD_SA_METHOD_GET_MULTI_RESP:
			return ("GetMultiResp");
		case UMAD_SA_METHOD_GET_TRACE_TABLE:
			return ("GetTraceTable");
		default:
			return (umad_common_method_str(method));
	}
}
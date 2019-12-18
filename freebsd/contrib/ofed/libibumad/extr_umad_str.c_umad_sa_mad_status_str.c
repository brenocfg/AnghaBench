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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  UMAD_SA_STATUS_INSUF_COMPS 136 
#define  UMAD_SA_STATUS_INVALID_GID 135 
#define  UMAD_SA_STATUS_NO_RECORDS 134 
#define  UMAD_SA_STATUS_NO_RESOURCES 133 
#define  UMAD_SA_STATUS_PRI_SUGGESTED 132 
#define  UMAD_SA_STATUS_REQ_DENIED 131 
#define  UMAD_SA_STATUS_REQ_INVALID 130 
#define  UMAD_SA_STATUS_SUCCESS 129 
#define  UMAD_SA_STATUS_TOO_MANY_RECORDS 128 
 int UMAD_STATUS_CLASS_MASK ; 
 int be16toh (int /*<<< orphan*/ ) ; 

const char * umad_sa_mad_status_str(__be16 _status)
{
	uint16_t status = be16toh(_status);
	switch((status & UMAD_STATUS_CLASS_MASK) >> 8) {
		case UMAD_SA_STATUS_SUCCESS:
			return ("Success");
		case UMAD_SA_STATUS_NO_RESOURCES:
			return ("No Resources");
		case UMAD_SA_STATUS_REQ_INVALID:
			return ("Request Invalid");
		case UMAD_SA_STATUS_NO_RECORDS:
			return ("No Records");
		case UMAD_SA_STATUS_TOO_MANY_RECORDS:
			return ("Too Many Records");
		case UMAD_SA_STATUS_INVALID_GID:
			return ("Invalid GID");
		case UMAD_SA_STATUS_INSUF_COMPS:
			return ("Insufficient Components");
		case UMAD_SA_STATUS_REQ_DENIED:
			return ("Request Denied");
		case UMAD_SA_STATUS_PRI_SUGGESTED:
			return ("Priority Suggested");
	}
	return ("Undefined Error");
}
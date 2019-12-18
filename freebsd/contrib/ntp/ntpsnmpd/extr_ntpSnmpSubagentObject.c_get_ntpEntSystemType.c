#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  requestvb; } ;
typedef  TYPE_1__ netsnmp_request_info ;
typedef  int /*<<< orphan*/  netsnmp_mib_handler ;
typedef  int /*<<< orphan*/  netsnmp_handler_registration ;
struct TYPE_6__ {int mode; } ;
typedef  TYPE_2__ netsnmp_agent_request_info ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_OCTET_STR ; 
#define  MODE_GET 128 
 int /*<<< orphan*/  NTPQ_BUFLEN ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 scalar_t__ ntpvalue ; 
 int /*<<< orphan*/  read_ntp_value (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_set_var_typed_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strlen (scalar_t__) ; 

int get_ntpEntSystemType (netsnmp_mib_handler *handler,
                               netsnmp_handler_registration *reginfo,
                               netsnmp_agent_request_info *reqinfo,
                               netsnmp_request_info *requests)
{

   switch (reqinfo->mode) {
   case MODE_GET:
   {
    
    if ( read_ntp_value("systemtype", ntpvalue, NTPQ_BUFLEN) )
    {
	snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                             (u_char *)ntpvalue,
                             strlen(ntpvalue)
                            );
    }
	   
    if ( read_ntp_value("system", ntpvalue, NTPQ_BUFLEN) )
    {
	snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                             (u_char *)ntpvalue,
                             strlen(ntpvalue)
                            );
    } else {
	snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                             (u_char *)"N/A",
                             3
                            );
    }
    break;
    
  }


  default:
	  /* If we cannot get the information we need, we will return a generic error to the SNMP client */
        return SNMP_ERR_GENERR;
  }

  return SNMP_ERR_NOERROR;
}
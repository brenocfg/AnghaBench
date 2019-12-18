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
typedef  int /*<<< orphan*/  ntp_softwarename ;
struct TYPE_5__ {int /*<<< orphan*/  requestvb; } ;
typedef  TYPE_1__ netsnmp_request_info ;
typedef  int /*<<< orphan*/  netsnmp_mib_handler ;
typedef  int /*<<< orphan*/  netsnmp_handler_registration ;
struct TYPE_6__ {int mode; } ;
typedef  TYPE_2__ netsnmp_agent_request_info ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_OCTET_STR ; 
#define  MODE_GET 128 
 int NTPQ_BUFLEN ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntpsnmpd_cut_string (char*,char*,char,int /*<<< orphan*/ ,int) ; 
 char* ntpvalue ; 
 int /*<<< orphan*/  read_ntp_value (char*,char*,int) ; 
 int /*<<< orphan*/  snmp_set_var_typed_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 

int get_ntpEntSoftwareName (netsnmp_mib_handler *handler,
                               netsnmp_handler_registration *reginfo,
                               netsnmp_agent_request_info *reqinfo,
                               netsnmp_request_info *requests)
{
 char ntp_softwarename[NTPQ_BUFLEN];
	
   memset (ntp_softwarename, 0, NTPQ_BUFLEN);
	
   switch (reqinfo->mode) {
   case MODE_GET:
   {
	if ( read_ntp_value("product", ntpvalue, NTPQ_BUFLEN) )
       {
	snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                             (u_char *)ntpvalue,
                             strlen(ntpvalue)
                            );
       } 
    else  if ( read_ntp_value("version", ntpvalue, NTPQ_BUFLEN) )
    {
	ntpsnmpd_cut_string(ntpvalue, ntp_softwarename, ' ', 0, sizeof(ntp_softwarename)-1);
	snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                             (u_char *)ntp_softwarename,
                             strlen(ntp_softwarename)
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
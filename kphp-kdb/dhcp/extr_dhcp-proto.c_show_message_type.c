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
typedef  enum dhcp_message_type { ____Placeholder_dhcp_message_type } dhcp_message_type ;

/* Variables and functions */
#define  dhcpmt_ack 135 
#define  dhcpmt_decline 134 
#define  dhcpmt_discover 133 
#define  dhcpmt_inform 132 
#define  dhcpmt_nak 131 
#define  dhcpmt_offer 130 
#define  dhcpmt_release 129 
#define  dhcpmt_request 128 

__attribute__((used)) static char *show_message_type (enum dhcp_message_type t) {
  switch (t) {
  case dhcpmt_discover: return "DHCPDISCOVER";
  case dhcpmt_offer: return "DHCPOFFER";
  case dhcpmt_request: return "DHCPREQUEST";
  case dhcpmt_decline: return "DHCPDECLINE";
  case dhcpmt_ack: return "DHCPACK";
  case dhcpmt_nak: return "DHCPNAK";
  case dhcpmt_release: return "DHCPRELEASE";
  case dhcpmt_inform: return "DHCPINFORM";
  }
  return NULL;
}
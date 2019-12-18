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
typedef  int /*<<< orphan*/  s ;
typedef  enum dhcp_option { ____Placeholder_dhcp_option } dhcp_option ;

/* Variables and functions */
#define  dhcpo_all_subnets_are_local 204 
#define  dhcpo_arp_cache_timeout 203 
#define  dhcpo_boot_file_size 202 
#define  dhcpo_bootfile_name 201 
#define  dhcpo_broadcast_address 200 
#define  dhcpo_client_identifier 199 
#define  dhcpo_cookie_server 198 
#define  dhcpo_default_finger_server 197 
#define  dhcpo_default_internet_relay_chat_server 196 
#define  dhcpo_default_ip_time_to_live 195 
#define  dhcpo_default_world_wide_web_server 194 
#define  dhcpo_dhcp_message_type 193 
#define  dhcpo_domain_name 192 
#define  dhcpo_domain_name_server 191 
#define  dhcpo_domain_search 190 
#define  dhcpo_end 189 
#define  dhcpo_ethernet_encapsulation 188 
#define  dhcpo_extensions_path 187 
#define  dhcpo_host_name 186 
#define  dhcpo_impress_server 185 
#define  dhcpo_interface_mtu_option 184 
#define  dhcpo_ip_address_lease_time 183 
#define  dhcpo_ip_forwarding 182 
#define  dhcpo_log_server 181 
#define  dhcpo_lpr_server 180 
#define  dhcpo_mask_supplier 179 
#define  dhcpo_maximum_datagram_reassembly_size 178 
#define  dhcpo_maximum_dhcp_message_size 177 
#define  dhcpo_merit_dump_file 176 
#define  dhcpo_message 175 
#define  dhcpo_mobile_ip_home_agent 174 
#define  dhcpo_name_server 173 
#define  dhcpo_netbios_over_tcp_ip_datagram_distribution_server 172 
#define  dhcpo_netbios_over_tcp_ip_name_server 171 
#define  dhcpo_netbios_over_tcp_ip_node_type 170 
#define  dhcpo_netbios_over_tcp_ip_scope 169 
#define  dhcpo_network_information_servers 168 
#define  dhcpo_network_information_service_domain 167 
#define  dhcpo_network_information_service_plus_domain 166 
#define  dhcpo_network_information_service_plus_servers 165 
#define  dhcpo_network_news_transport_protocol_server 164 
#define  dhcpo_network_time_protocol_servers 163 
#define  dhcpo_non_local_source_routing 162 
#define  dhcpo_overload 161 
#define  dhcpo_pad 160 
#define  dhcpo_parameter_request_list 159 
#define  dhcpo_path_mtu_aging_timeout 158 
#define  dhcpo_path_mtu_plateau_table 157 
#define  dhcpo_perform_mask_discovery 156 
#define  dhcpo_perform_router_discovery 155 
#define  dhcpo_policy_filter 154 
#define  dhcpo_post_office_protocol_server 153 
#define  dhcpo_rebinding_time_value 152 
#define  dhcpo_renewal_time_value 151 
#define  dhcpo_requested_ip_address 150 
#define  dhcpo_resource_location_server 149 
#define  dhcpo_root_path 148 
#define  dhcpo_router 147 
#define  dhcpo_router_solicitation_address 146 
#define  dhcpo_server_identifier 145 
#define  dhcpo_simple_mail_transport_protocol_server 144 
#define  dhcpo_static_route 143 
#define  dhcpo_streettalk_directory_assistance_server 142 
#define  dhcpo_streettalk_server 141 
#define  dhcpo_subnet_mask 140 
#define  dhcpo_swap_server 139 
#define  dhcpo_tcp_default_ttl 138 
#define  dhcpo_tcp_keepalive_garbage 137 
#define  dhcpo_tcp_keepalive_interval 136 
#define  dhcpo_tftp_server_name 135 
#define  dhcpo_time_offset 134 
#define  dhcpo_time_server 133 
#define  dhcpo_trailer_encapsulation 132 
#define  dhcpo_vendor_class_identifier 131 
#define  dhcpo_vendor_specific 130 
#define  dhcpo_x_window_system_display_manager 129 
#define  dhcpo_x_window_system_font_server 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *show_option (enum dhcp_option o) {
  switch (o) {
  case dhcpo_pad: return "Pad";
  case dhcpo_end: return "End";
  case dhcpo_subnet_mask: return "Subnet Mask";
  case dhcpo_time_offset: return "Time Offset";
  case dhcpo_router: return "Router";
  case dhcpo_time_server: return "Time Server";
  case dhcpo_name_server: return "Name Server";
  case dhcpo_domain_name_server: return "Domain Name Server";
  case dhcpo_log_server: return "Log Server";
  case dhcpo_cookie_server: return "Cookie Server";
  case dhcpo_lpr_server: return "LPR Server";
  case dhcpo_impress_server: return "Impress Server";
  case dhcpo_resource_location_server: return "Resource Location Server";
  case dhcpo_host_name: return "Host Name";
  case dhcpo_boot_file_size: return "Boot File Size";
  case dhcpo_merit_dump_file: return "Merit Dump File";
  case dhcpo_domain_name: return "Domain Name";
  case dhcpo_swap_server: return "Swap Server";
  case dhcpo_root_path: return "Root Path";
  case dhcpo_extensions_path: return "Extensions Path";
  case dhcpo_ip_forwarding: return "IP Forwarding";
  case dhcpo_non_local_source_routing: return "Non-Local Source Routing";
  case dhcpo_policy_filter: return "Policy Filter";
  case dhcpo_maximum_datagram_reassembly_size: return "Maximum Datagram Reassembly Size";
  case dhcpo_default_ip_time_to_live: return "Default IP Time-to-live";
  case dhcpo_path_mtu_aging_timeout: return "Path MTU Aging Timeout";
  case dhcpo_path_mtu_plateau_table: return "Path MTU Plateau Table";
  case dhcpo_interface_mtu_option: return "Interface MTU Option";
  case dhcpo_all_subnets_are_local: return "All Subnets are Local";
  case dhcpo_broadcast_address: return "Broadcast Address";
  case dhcpo_perform_mask_discovery: return "Perform Mask Discovery";
  case dhcpo_mask_supplier: return "Mask Supplier";
  case dhcpo_perform_router_discovery: return "Perform Router Discovery";
  case dhcpo_router_solicitation_address: return "Router Solicitation Address";
  case dhcpo_static_route: return "Static Route";
  case dhcpo_trailer_encapsulation: return "Trailer Encapsulation";
  case dhcpo_arp_cache_timeout: return "ARP Cache Timeout";
  case dhcpo_ethernet_encapsulation: return "Ethernet Encapsulation";
  case dhcpo_tcp_default_ttl: return "TCP Default TTL";
  case dhcpo_tcp_keepalive_interval: return "TCP Keepalive Interval";
  case dhcpo_tcp_keepalive_garbage: return "TCP Keepalive Garbage";
  case dhcpo_network_information_service_domain: return "Network Information Service Domain";
  case dhcpo_network_information_servers: return "Network Information Servers";
  case dhcpo_network_time_protocol_servers: return "Network Time Protocol Servers";
  case dhcpo_vendor_specific: return "Vendor Specific";
  case dhcpo_netbios_over_tcp_ip_name_server: return "NetBIOS over TCP/IP Name Server";
  case dhcpo_netbios_over_tcp_ip_datagram_distribution_server: return "NetBIOS over TCP/IP Datagram Distribution Server";
  case dhcpo_netbios_over_tcp_ip_node_type: return "NetBIOS over TCP/IP Node Type";
  case dhcpo_netbios_over_tcp_ip_scope: return "NetBIOS over TCP/IP Scope";
  case dhcpo_x_window_system_font_server: return "X Window System Font Server";
  case dhcpo_x_window_system_display_manager: return "X Window System Display Manager";
  case dhcpo_network_information_service_plus_domain: return "Network Information Service+ Domain";
  case dhcpo_network_information_service_plus_servers: return "Network Information Service+ Servers";
  case dhcpo_mobile_ip_home_agent: return "Mobile IP Home Agent";
  case dhcpo_simple_mail_transport_protocol_server: return "Simple Mail Transport Protocol Server";
  case dhcpo_post_office_protocol_server: return "Post Office Protocol Server";
  case dhcpo_network_news_transport_protocol_server: return "Network News Transport Protocol Server";
  case dhcpo_default_world_wide_web_server: return "Default World Wide Web Server";
  case dhcpo_default_finger_server: return "Default Finger Server";
  case dhcpo_default_internet_relay_chat_server: return "Default Internet Relay Chat Server";
  case dhcpo_streettalk_server: return "StreetTalk Server";
  case dhcpo_streettalk_directory_assistance_server: return "StreetTalk Directory Assistance Server";
  case dhcpo_requested_ip_address: return "Requested IP Address";
  case dhcpo_ip_address_lease_time: return "IP Address Lease Time";
  case dhcpo_overload: return "Overload";
  case dhcpo_tftp_server_name: return "TFTP server name";
  case dhcpo_bootfile_name: return "Bootfile name";
  case dhcpo_dhcp_message_type: return "DHCP Message Type";
  case dhcpo_server_identifier: return "Server Identifier";
  case dhcpo_parameter_request_list: return "Parameter Request List";
  case dhcpo_message: return "Message";
  case dhcpo_maximum_dhcp_message_size: return "Maximum DHCP Message Size";
  case dhcpo_renewal_time_value: return "Renewal Time Value";
  case dhcpo_rebinding_time_value: return "Rebinding Time Value";
  case dhcpo_vendor_class_identifier: return "Vendor class identifier";
  case dhcpo_client_identifier: return "Client-identifier";
  case dhcpo_domain_search: return "Domain Search";
  }
  static char s[128];
  snprintf (s, sizeof (s), "Unknown opcode %d", o);
  return s;
}
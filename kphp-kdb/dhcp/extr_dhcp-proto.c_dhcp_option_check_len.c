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

__attribute__((used)) static int dhcp_option_check_len (enum dhcp_option o, int len) {
  switch (o) {
  case dhcpo_pad:
  case dhcpo_end:
    return len == 0;
  case dhcpo_ip_forwarding:
  case dhcpo_non_local_source_routing:
  case dhcpo_default_ip_time_to_live:
  case dhcpo_all_subnets_are_local:
  case dhcpo_perform_mask_discovery:
  case dhcpo_mask_supplier:
  case dhcpo_perform_router_discovery:
  case dhcpo_trailer_encapsulation:
  case dhcpo_ethernet_encapsulation:
  case dhcpo_tcp_default_ttl:
  case dhcpo_tcp_keepalive_garbage:
  case dhcpo_netbios_over_tcp_ip_node_type:
  case dhcpo_overload:
  case dhcpo_dhcp_message_type:
    return len == 1;
  case dhcpo_boot_file_size:
  case dhcpo_maximum_datagram_reassembly_size:
  case dhcpo_interface_mtu_option:
  case dhcpo_maximum_dhcp_message_size:
    return len == 2;
  case dhcpo_subnet_mask:
  case dhcpo_time_offset:
  case dhcpo_path_mtu_aging_timeout:
  case dhcpo_broadcast_address:
  case dhcpo_router_solicitation_address:
  case dhcpo_arp_cache_timeout:
  case dhcpo_tcp_keepalive_interval:
  case dhcpo_requested_ip_address:
  case dhcpo_ip_address_lease_time:
  case dhcpo_server_identifier:
  case dhcpo_renewal_time_value:
  case dhcpo_rebinding_time_value:
    return len == 4;
  case dhcpo_host_name:
  case dhcpo_merit_dump_file:
  case dhcpo_domain_name:
  case dhcpo_root_path:
  case dhcpo_extensions_path:
  case dhcpo_network_information_service_domain:
  case dhcpo_network_information_service_plus_domain:
  case dhcpo_tftp_server_name:
  case dhcpo_bootfile_name:
  case dhcpo_parameter_request_list:
  case dhcpo_message:
  case dhcpo_domain_search:
    return len >= 1;
  case dhcpo_path_mtu_plateau_table:
    return len >= 2 && !(len & 1);
  case dhcpo_mobile_ip_home_agent:
    return len >= 0 && !(len & 3);
  case dhcpo_router:
  case dhcpo_time_server:
  case dhcpo_name_server:
  case dhcpo_domain_name_server:
  case dhcpo_log_server:
  case dhcpo_cookie_server:
  case dhcpo_lpr_server:
  case dhcpo_impress_server:
  case dhcpo_resource_location_server:
  case dhcpo_swap_server:
  case dhcpo_network_information_servers:
  case dhcpo_network_time_protocol_servers:
  case dhcpo_netbios_over_tcp_ip_name_server:
  case dhcpo_netbios_over_tcp_ip_datagram_distribution_server:
  case dhcpo_x_window_system_font_server:
  case dhcpo_x_window_system_display_manager:
  case dhcpo_network_information_service_plus_servers:
  case dhcpo_simple_mail_transport_protocol_server:
  case dhcpo_post_office_protocol_server:
  case dhcpo_network_news_transport_protocol_server:
  case dhcpo_default_world_wide_web_server:
  case dhcpo_default_finger_server:
  case dhcpo_default_internet_relay_chat_server:
  case dhcpo_streettalk_server:
  case dhcpo_streettalk_directory_assistance_server:
    return len >= 4 && !(len & 3);
  case dhcpo_policy_filter:
  case dhcpo_static_route:
    return len >= 8 && !(len & 7);
  case dhcpo_vendor_specific:
  case dhcpo_netbios_over_tcp_ip_scope:
  case dhcpo_vendor_class_identifier:
  case dhcpo_client_identifier:
    return len >= 0;
  }
  return 0;
}
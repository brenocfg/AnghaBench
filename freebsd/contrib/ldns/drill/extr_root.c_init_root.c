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
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 int /*<<< orphan*/  global_dns_root ; 
 int /*<<< orphan*/  ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_new_frm_str (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
init_root(void)
{
	ldns_rr *r;
	
	global_dns_root = ldns_rr_list_new();

	(void)ldns_rr_new_frm_str(&r, "A.ROOT-SERVERS.NET.      3600000      A     198.41.0.4", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "A.ROOT-SERVERS.NET.      3600000      AAAA  2001:503:BA3E::2:30", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "B.ROOT-SERVERS.NET.      3600000      A     192.228.79.201", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "C.ROOT-SERVERS.NET.      3600000      A     192.33.4.12", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "D.ROOT-SERVERS.NET.      3600000      A     128.8.10.90", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "E.ROOT-SERVERS.NET.      3600000      A     192.203.230.10", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "F.ROOT-SERVERS.NET.      3600000      A     192.5.5.241", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "F.ROOT-SERVERS.NET.      3600000      AAAA  2001:500:2F::F", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "G.ROOT-SERVERS.NET.      3600000      A     192.112.36.4", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "H.ROOT-SERVERS.NET.      3600000      A     128.63.2.53", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "H.ROOT-SERVERS.NET.      3600000      AAAA  2001:500:1::803F:235", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "I.ROOT-SERVERS.NET.      3600000      A     192.36.148.17", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "J.ROOT-SERVERS.NET.      3600000      A     192.58.128.30", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "J.ROOT-SERVERS.NET.      3600000      AAAA  2001:503:C27::2:30", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "K.ROOT-SERVERS.NET.      3600000      A     193.0.14.129 ", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "K.ROOT-SERVERS.NET.      3600000      AAAA  2001:7FD::1", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "L.ROOT-SERVERS.NET.      3600000      A     199.7.83.42", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "L.ROOT-SERVERS.NET.      3600000      AAAA  2001:500:3::42   ", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "M.ROOT-SERVERS.NET.      3600000      A     202.12.27.33", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
	(void)ldns_rr_new_frm_str(&r, "M.ROOT-SERVERS.NET.      3600000      AAAA  2001:DC3::35", 0, NULL, NULL);
	ldns_rr_list_push_rr(global_dns_root, r);
}
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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int init_antispam_data (int) ; 
 int init_bayes_data (int) ; 
 int init_cache_data (int) ; 
 int init_copyexec_aux_data (int) ; 
 int init_copyexec_main_data (int) ; 
 int init_copyexec_result_data (int) ; 
 int init_dns_data (int) ; 
 int init_filesys_data (int) ; 
 int init_friends_data (int) ; 
 int init_gms_data (int) ; 
 int init_gms_money_data (int) ; 
 int init_hints_data (int) ; 
 int init_isearch_data (int) ; 
 int init_lists_data (int) ; 
 int init_logs_data (int) ; 
 int init_magus_data (int) ; 
 int init_mf_data (int) ; 
 int init_money_data (int) ; 
 int init_news_data (int) ; 
 int init_password_data (int) ; 
 int init_photo_data (int) ; 
 int init_pmemcached_data (int) ; 
 int init_rpc_proxy_data (int) ; 
 int init_search_data (int) ; 
 int init_seqmap_data (int) ; 
 int init_sql_data (int) ; 
 int init_stats_data (int) ; 
 int init_storage_data (int) ; 
 int init_support_data (int) ; 
 int init_targ_data (int) ; 
 int init_text_data (int) ; 
 int init_weights_data (int) ; 
 int log_schema ; 
 int /*<<< orphan*/  stderr ; 

int set_schema (int schema) {
  int res = -1;
  switch (schema & (-1 << 16)) {
  case 0x6ba30000:
    res = init_targ_data (schema);
    break;
  case 0x3ae60000:
    res = init_stats_data (schema);
    break;
  case 0xbeef0000:
    res = init_search_data (schema);
    break;  
  case 0x2bec0000:
    res = init_friends_data (schema);
    break;
  case 0x53c40000:
    res = init_news_data (schema);
    break;
  case 0x6ef20000:
    res = init_lists_data (schema);
    break;
  case 0x2cb30000:
    res = init_text_data (schema);
    break;
  case 0xf00d0000:
    res = init_money_data (schema);
    break;
  case 0x4fad0000:
    res = init_hints_data (schema);
    break;
  case 0x3ad50000:
    res = init_bayes_data (schema);
    break;
  case 0x7a9c0000:
    res = init_magus_data (schema);
    break;
  case 0x5f180000:
    res = init_photo_data (schema);
    break;
  case 0xafe60000:
    res = init_mf_data (schema);
    break;
  case 0x5fad0000:
    res = init_isearch_data (schema);
    break;
  case 0x21090000:
    res = init_logs_data (schema);
    break;
  case 0x37450000:
    res = init_pmemcached_data (schema);
    break;
  case 0xfa730000:
    res = init_sql_data (schema);
    break;
  case 0x65510000:
    res = init_password_data (schema);
    break;
  case 0x723d0000:
    res = init_filesys_data (schema);
    break;
  case 0x3ded0000:
    res = init_cache_data (schema);
    break;
  case 0x521e0000:
    res = init_weights_data (schema);
    break;
  case 0x144a0000:
    res = init_dns_data (schema);
    break;
  case 0x805a0000:
    res = init_storage_data (schema);
    break;
  case 0x1fec0000:
    res = init_support_data (schema);
    break;
  case 0x91a70000:
    res = init_antispam_data (schema);
    break;
  case 0x29790000:
    res = init_copyexec_aux_data (schema);
    break;
  case 0xeda90000:
    res = init_copyexec_main_data (schema);
    break;
  case 0xedaa0000:
    res = init_copyexec_result_data (schema);
    break;
  case 0x8f6a0000:
    res = init_gms_data (schema);
    break;
  case 0xfa8f0000:
    res = init_gms_money_data (schema);
    break;
  case 0x8f0e0000:
    res = init_seqmap_data (schema);
    break;
  case 0xf9a90000:
    res = init_rpc_proxy_data (schema);
    break;
  }
  if (res >= 0) {
    log_schema = schema;
  } else {
    fprintf (stderr, "unknown schema: %08x\n", schema);
  }
  return res;
}
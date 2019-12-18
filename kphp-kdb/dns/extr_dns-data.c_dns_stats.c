#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double percent_label_buff; double percent_record_buff; double percent_nodes; double percent_edges; } ;
typedef  TYPE_1__ dns_stat_t ;

/* Variables and functions */
 double DNS_LABELS_BUFFSIZE ; 
 double DNS_MAX_TRIE_EDGES ; 
 double DNS_MAX_TRIE_NODES ; 
 double DNS_RECORDS_BUFFSIZE ; 
 double labels_saved_bytes ; 
 double labels_wptr ; 
 double records_wptr ; 
 double trie_edges ; 
 double trie_nodes ; 

void dns_stats (dns_stat_t *S) {
  S->percent_label_buff = (labels_wptr * 100.0) / DNS_LABELS_BUFFSIZE;
  S->percent_label_buff = (labels_saved_bytes * 100.0) / DNS_LABELS_BUFFSIZE;
  S->percent_record_buff = (records_wptr * 100.0) / DNS_RECORDS_BUFFSIZE;
  S->percent_nodes = (trie_nodes * 100.0) / DNS_MAX_TRIE_NODES;
  S->percent_edges = (trie_edges * 100.0) / DNS_MAX_TRIE_EDGES;
}
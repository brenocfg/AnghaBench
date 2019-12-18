#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ max_query_list_size; scalar_t__* hist; scalar_t__* ans_rcode; scalar_t__* qopcode; scalar_t__* qclass; scalar_t__* qtype; scalar_t__ tcp_accept_usage; scalar_t__ unwanted_queries; scalar_t__ unwanted_replies; scalar_t__ ans_bogus; scalar_t__ ans_secure; scalar_t__ zero_ttl_responses; scalar_t__ ans_rcode_nodata; scalar_t__ qEDNS_DO; scalar_t__ qEDNS; scalar_t__ qbit_CD; scalar_t__ qbit_AD; scalar_t__ qbit_Z; scalar_t__ qbit_RA; scalar_t__ qbit_RD; scalar_t__ qbit_TC; scalar_t__ qbit_AA; scalar_t__ qbit_QR; scalar_t__ qipv6; scalar_t__ qtls_resume; scalar_t__ qtls; scalar_t__ qtcp_outgoing; scalar_t__ qtcp; scalar_t__ qclass_big; scalar_t__ qtype_big; scalar_t__ extended; scalar_t__ num_query_dnscrypt_crypted_malformed; scalar_t__ num_query_dnscrypt_cleartext; scalar_t__ num_query_dnscrypt_cert; scalar_t__ num_query_dnscrypt_crypted; scalar_t__ sum_query_list_size; scalar_t__ num_queries_prefetch; scalar_t__ num_queries_missed_cache; scalar_t__ num_queries_ip_ratelimited; scalar_t__ num_queries; } ;
struct ub_stats_info {scalar_t__ mesh_time_median; int /*<<< orphan*/  mesh_replies_sum_wait_usec; int /*<<< orphan*/  mesh_replies_sum_wait_sec; scalar_t__ mesh_replies_sent; scalar_t__ mesh_dropped; scalar_t__ mesh_jostled; scalar_t__ mesh_num_reply_states; scalar_t__ mesh_num_states; TYPE_1__ svr; } ;

/* Variables and functions */
 int NUM_BUCKETS_HIST ; 
 int UB_STATS_OPCODE_NUM ; 
 int UB_STATS_QCLASS_NUM ; 
 int UB_STATS_QTYPE_NUM ; 
 int UB_STATS_RCODE_NUM ; 
 int /*<<< orphan*/  stats_timeval_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void server_stats_add(struct ub_stats_info* total, struct ub_stats_info* a)
{
	total->svr.num_queries += a->svr.num_queries;
	total->svr.num_queries_ip_ratelimited += a->svr.num_queries_ip_ratelimited;
	total->svr.num_queries_missed_cache += a->svr.num_queries_missed_cache;
	total->svr.num_queries_prefetch += a->svr.num_queries_prefetch;
	total->svr.sum_query_list_size += a->svr.sum_query_list_size;
#ifdef USE_DNSCRYPT
	total->svr.num_query_dnscrypt_crypted += a->svr.num_query_dnscrypt_crypted;
	total->svr.num_query_dnscrypt_cert += a->svr.num_query_dnscrypt_cert;
	total->svr.num_query_dnscrypt_cleartext += \
		a->svr.num_query_dnscrypt_cleartext;
	total->svr.num_query_dnscrypt_crypted_malformed += \
		a->svr.num_query_dnscrypt_crypted_malformed;
#endif /* USE_DNSCRYPT */
	/* the max size reached is upped to higher of both */
	if(a->svr.max_query_list_size > total->svr.max_query_list_size)
		total->svr.max_query_list_size = a->svr.max_query_list_size;

	if(a->svr.extended) {
		int i;
		total->svr.qtype_big += a->svr.qtype_big;
		total->svr.qclass_big += a->svr.qclass_big;
		total->svr.qtcp += a->svr.qtcp;
		total->svr.qtcp_outgoing += a->svr.qtcp_outgoing;
		total->svr.qtls += a->svr.qtls;
		total->svr.qtls_resume += a->svr.qtls_resume;
		total->svr.qipv6 += a->svr.qipv6;
		total->svr.qbit_QR += a->svr.qbit_QR;
		total->svr.qbit_AA += a->svr.qbit_AA;
		total->svr.qbit_TC += a->svr.qbit_TC;
		total->svr.qbit_RD += a->svr.qbit_RD;
		total->svr.qbit_RA += a->svr.qbit_RA;
		total->svr.qbit_Z += a->svr.qbit_Z;
		total->svr.qbit_AD += a->svr.qbit_AD;
		total->svr.qbit_CD += a->svr.qbit_CD;
		total->svr.qEDNS += a->svr.qEDNS;
		total->svr.qEDNS_DO += a->svr.qEDNS_DO;
		total->svr.ans_rcode_nodata += a->svr.ans_rcode_nodata;
		total->svr.zero_ttl_responses += a->svr.zero_ttl_responses;
		total->svr.ans_secure += a->svr.ans_secure;
		total->svr.ans_bogus += a->svr.ans_bogus;
		total->svr.unwanted_replies += a->svr.unwanted_replies;
		total->svr.unwanted_queries += a->svr.unwanted_queries;
		total->svr.tcp_accept_usage += a->svr.tcp_accept_usage;
		for(i=0; i<UB_STATS_QTYPE_NUM; i++)
			total->svr.qtype[i] += a->svr.qtype[i];
		for(i=0; i<UB_STATS_QCLASS_NUM; i++)
			total->svr.qclass[i] += a->svr.qclass[i];
		for(i=0; i<UB_STATS_OPCODE_NUM; i++)
			total->svr.qopcode[i] += a->svr.qopcode[i];
		for(i=0; i<UB_STATS_RCODE_NUM; i++)
			total->svr.ans_rcode[i] += a->svr.ans_rcode[i];
		for(i=0; i<NUM_BUCKETS_HIST; i++)
			total->svr.hist[i] += a->svr.hist[i];
	}

	total->mesh_num_states += a->mesh_num_states;
	total->mesh_num_reply_states += a->mesh_num_reply_states;
	total->mesh_jostled += a->mesh_jostled;
	total->mesh_dropped += a->mesh_dropped;
	total->mesh_replies_sent += a->mesh_replies_sent;
	stats_timeval_add(&total->mesh_replies_sum_wait_sec, &total->mesh_replies_sum_wait_usec, a->mesh_replies_sum_wait_sec, a->mesh_replies_sum_wait_usec);
	/* the medians are averaged together, this is not as accurate as
	 * taking the median over all of the data, but is good and fast
	 * added up here, division later*/
	total->mesh_time_median += a->mesh_time_median;
}
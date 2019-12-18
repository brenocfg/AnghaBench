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
struct tcp_log_mem {int dummy; } ;
struct tcp_log_id_node {int dummy; } ;
struct tcp_log_id_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RW_NEW ; 
 int /*<<< orphan*/  TCP_LOG_BUF_DEFAULT_GLOBAL_LIMIT ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 void* counter_u64_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_id_tree_lock ; 
 void* tcp_log_bucket_zone ; 
 int /*<<< orphan*/  tcp_log_expireq_callout ; 
 int /*<<< orphan*/  tcp_log_expireq_mtx ; 
 void* tcp_log_node_zone ; 
 void* tcp_log_que_copyout ; 
 void* tcp_log_que_fail1 ; 
 void* tcp_log_que_fail2 ; 
 void* tcp_log_que_fail3 ; 
 void* tcp_log_que_fail4 ; 
 void* tcp_log_que_fail5 ; 
 void* tcp_log_que_freed ; 
 void* tcp_log_que_read ; 
 void* tcp_log_queued ; 
 void* tcp_log_zone ; 
 int /*<<< orphan*/  tcp_log_zone_ctor ; 
 int /*<<< orphan*/  tcp_log_zone_dtor ; 
 int /*<<< orphan*/  tcp_log_zone_init ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  uma_zone_set_max (void*,int /*<<< orphan*/ ) ; 

void
tcp_log_init(void)
{

	tcp_log_zone = uma_zcreate("tcp_log", sizeof(struct tcp_log_mem),
#ifdef TCPLOG_DEBUG_RINGBUF
	    tcp_log_zone_ctor, tcp_log_zone_dtor, tcp_log_zone_init,
#else
	    NULL, NULL, NULL,
#endif
	    NULL, UMA_ALIGN_PTR, 0);
	(void)uma_zone_set_max(tcp_log_zone, TCP_LOG_BUF_DEFAULT_GLOBAL_LIMIT);
	tcp_log_bucket_zone = uma_zcreate("tcp_log_bucket",
	    sizeof(struct tcp_log_id_bucket), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
	tcp_log_node_zone = uma_zcreate("tcp_log_node",
	    sizeof(struct tcp_log_id_node), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
#ifdef TCPLOG_DEBUG_COUNTERS
	tcp_log_queued = counter_u64_alloc(M_WAITOK);
	tcp_log_que_fail1 = counter_u64_alloc(M_WAITOK);
	tcp_log_que_fail2 = counter_u64_alloc(M_WAITOK);
	tcp_log_que_fail3 = counter_u64_alloc(M_WAITOK);
	tcp_log_que_fail4 = counter_u64_alloc(M_WAITOK);
	tcp_log_que_fail5 = counter_u64_alloc(M_WAITOK);
	tcp_log_que_copyout = counter_u64_alloc(M_WAITOK);
	tcp_log_que_read = counter_u64_alloc(M_WAITOK);
	tcp_log_que_freed = counter_u64_alloc(M_WAITOK);
#endif

	rw_init_flags(&tcp_id_tree_lock, "TCP ID tree", RW_NEW);
	mtx_init(&tcp_log_expireq_mtx, "TCP log expireq", NULL, MTX_DEF);
	callout_init(&tcp_log_expireq_callout, 1);
}
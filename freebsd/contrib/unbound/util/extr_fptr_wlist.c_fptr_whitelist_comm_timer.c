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
 void auth_xfer_probe_timer_callback (void*) ; 
 void auth_xfer_timer (void*) ; 
 void auth_xfer_transfer_timer_callback (void*) ; 
 void outnet_tcptimer (void*) ; 
 void pending_udp_timer_cb (void*) ; 
 void pending_udp_timer_delay_cb (void*) ; 
 void worker_probe_timer_cb (void*) ; 
 void worker_stat_timer_cb (void*) ; 
 void wsvc_cron_cb (void*) ; 

int 
fptr_whitelist_comm_timer(void (*fptr)(void*))
{
	if(fptr == &pending_udp_timer_cb) return 1;
	else if(fptr == &outnet_tcptimer) return 1;
	else if(fptr == &pending_udp_timer_delay_cb) return 1;
	else if(fptr == &worker_stat_timer_cb) return 1;
	else if(fptr == &worker_probe_timer_cb) return 1;
#ifdef UB_ON_WINDOWS
	else if(fptr == &wsvc_cron_cb) return 1;
#endif
	else if(fptr == &auth_xfer_timer) return 1;
	else if(fptr == &auth_xfer_probe_timer_callback) return 1;
	else if(fptr == &auth_xfer_transfer_timer_callback) return 1;
	return 0;
}
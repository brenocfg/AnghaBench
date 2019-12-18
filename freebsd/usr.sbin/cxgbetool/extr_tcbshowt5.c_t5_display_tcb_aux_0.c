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
typedef  int /*<<< orphan*/  _TCBVAR ;

/* Variables and functions */
 int /*<<< orphan*/  PR (char*,...) ; 
 int SEQ_SUB (int,int) ; 
 int /*<<< orphan*/  spr_cctrl_sel (int,int) ; 
 int /*<<< orphan*/  spr_ip_version (int) ; 
 int /*<<< orphan*/  spr_tcp_state (int) ; 
 int /*<<< orphan*/  spr_ulp_type (int) ; 
 int val (char*) ; 

void t5_display_tcb_aux_0 (_TCBVAR *tvp, int aux)
{






  
  PR("STATE:\n");
  PR("  %-12s (%-2u), %s, lock_tid %u, rss_fw %u\n",
	      spr_tcp_state(val("t_state")), 
	      val("t_state"),
	      spr_ip_version(val("ip_version")),
	      val("lock_tid"),
	      val("rss_fw")
	     );
  PR("  l2t_ix 0x%x, smac sel 0x%x, tos 0x%x\n",
	      val("l2t_ix"),
	      val("smac_sel"),
	      val("tos")
	      );
  PR("  maxseg %u, recv_scaleflag %u, recv_tstmp %u, recv_sack %u\n",
	      val("t_maxseg"),   val("recv_scale"),
	      val("recv_tstmp"), val("recv_sack"));


  PR("TIMERS:\n"); /* **************************************** */
  PR("  timer    %u,  dack_timer      %u\n", 
	   val("timer"), val("dack_timer"));
  PR("  mod_schd: tx: %u, rx: %u, reason 0x%1x\n", 
	      val("mod_schd_tx"), 
	      val("mod_schd_rx"),
	      ((val("mod_schd_reason2")<<2) | (val("mod_schd_reason1")<<1) |
	       val("mod_schd_reason0"))
	      );


  PR("  max_rt   %-2u, rxtshift        %u, keepalive   %u\n", 
	   val("max_rt"),  val("t_rxtshift"), 
	   val("keepalive"));
  PR("  timestamp_offset 0x%x,  timestamp 0x%x\n",
	   val("timestamp_offset"),val("timestamp"));


  PR("  t_rtt_ts_recent_age %u  t_rttseq_recent %u\n", 
	   val("t_rtt_ts_recent_age"), val("t_rtseq_recent"));
  PR("  t_srtt %u, t_rttvar %u\n",
	   val("t_srtt"),val("t_rttvar"));






  PR("TRANSMIT BUFFER:\n");   /* *************************** */
  PR("  snd_una %u, snd_nxt %u, snd_max %u, tx_max %u\n",
	      val("snd_una"),val("snd_nxt"),
	      val("snd_max"),val("tx_max"));
  PR("  core_fin %u, tx_hdr_offset %u\n",  
	      val("core_fin"), SEQ_SUB(val("tx_max"),val("snd_una"))
	     );
  if (val("recv_scale") && !val("active_open")) {
    PR("  rcv_adv    %-5u << %-2u == %u (recv_scaleflag %u rcv_scale %u active open %u)\n",
		val("rcv_adv"), val("rcv_scale"), 
		val("rcv_adv") << val("rcv_scale"), 
		val("recv_scale"), val("rcv_scale"), val("active_open"));
  } else {
    PR("  rcv_adv    %-5u (rcv_scale %-2u recv_scaleflag %u active_open %u)\n",
		val("rcv_adv"), val("rcv_scale"), 
		val("recv_scale"), val("active_open"));
  }
  
  PR("  snd_cwnd   %-5u  snd_ssthresh %u  snd_rec %u\n",
	      val("snd_cwnd")    , val("snd_ssthresh"), val("snd_rec")
	     );




  PR("  cctrl: sel %s, ecn %u, ece %u, cwr %u, rfr %u\n",
	      spr_cctrl_sel(val("cctrl_sel0"),val("cctrl_sel1")),
	      val("cctrl_ecn"), val("cctrl_ece"), val("cctrl_cwr"),
	      val("cctrl_rfr"));
  PR("  t_dupacks %u, dupack_count_odd %u, fast_recovery %u\n",
	      val("t_dupacks"), val("dupack_count_odd"),val("fast_recovery"));
  PR("  core_more    %u, core_urg,       %u  core_push   %u,",
	      val("core_more"),val("core_urg"),val("core_push"));
  PR("  core_flush %u\n",val("core_flush"));
  PR("  nagle        %u, ssws_disable    %u, turbo       %u,",
	      val("nagle"), val("ssws_disabled"), val("turbo"));
  PR("  tx_pdu_out %u\n",val("tx_pdu_out"));
  PR("  tx_pace_auto %u, tx_pace_fixed   %u, tx_queue    %u",
	      val("tx_pace_auto"),val("tx_pace_fixed"),val("tx_queue"));


  PR("   tx_quiesce %u\n",val("tx_quiesce"));
  PR("  tx_channel   %u, tx_channel1     %u, tx_channel0 %u\n",
	      val("tx_channel"),
	      (val("tx_channel")>>1)&1,
	      val("tx_channel")&1
	      );




  PR("  tx_hdr_ptr   0x%-6x   tx_last_ptr 0x%-6x  tx_compact %u\n", 
	      val("tx_hdr_ptr"),val("tx_last_ptr"),val("tx_compact"));




  PR("RECEIVE BUFFER:\n");  /* *************************** */
  PR("  last_ack_sent %-10u                      rx_compact %u\n", 
	      val("ts_last_ack_sent"),val("rx_compact"));
  PR("  rcv_nxt       %-10u  hdr_off %-10u\n",
	      val("rcv_nxt"), val("rx_hdr_offset"));
  PR("  frag0_idx     %-10u  length  %-10u  rx_ptr  0x%-8x\n", 
	      val("rx_frag0_start_idx"),
	      val("rx_frag0_len"),
	      val("rx_ptr"));
  PR("  frag1_idx     %-10u  length  %-10u  ", 
	      val("rx_frag1_start_idx_offset"),
	      val("rx_frag1_len"));




  if (val("ulp_type")!=4) { /* RDMA has FRAG1 idx && len, but no ptr?  Should I not display frag1 at all? */
    PR("frag1_ptr  0x%-8x\n",val("rx_frag1_ptr"));
  } else {
    PR("\n");
  }
	      
  
  if (val("ulp_type") !=6 && val("ulp_type") != 5 && val("ulp_type") !=4) {
    PR("  frag2_idx     %-10u  length  %-10u  frag2_ptr  0x%-8x\n", 
		val("rx_frag2_start_idx_offset"),
		val("rx_frag2_len"),
		val("rx_frag2_ptr"));
    PR("  frag3_idx     %-10u  length  %-10u  frag3_ptr  0x%-8x\n", 
		val("rx_frag3_start_idx_offset"),
		val("rx_frag3_len"),
		val("rx_frag3_ptr"));
  }






  PR("  peer_fin %u,   rx_pdu_out %u, pdu_len %u\n",
	      val("peer_fin"),val("rx_pdu_out"), val("pdu_len"));




  if (val("recv_scale")) {
    PR("  rcv_wnd %u >> snd_scale %u == %u, recv_scaleflag = %u\n",
		val("rcv_wnd"), val("snd_scale"), 
		val("rcv_wnd") >> val("snd_scale"), 
		val("recv_scale"));
  } else {
    PR("  rcv_wnd %u.  (snd_scale %u, recv_scaleflag = %u)\n",
		val("rcv_wnd"), val("snd_scale"), 
		val("recv_scale"));
  }




 PR("  dack_mss   %u dack       %u,  dack_not_acked: %u\n", 
	      val("dack_mss"),val("dack"),val("dack_not_acked"));
  PR("  rcv_coal   %u rcv_co_psh %u rcv_co_last_psh  %u heart %u\n",
	      val("rcv_coalesce_enable"),
	      val("rcv_coalesce_push"),
	      val("rcv_coalesce_last_psh"),
	      val("rcv_coalesce_heartbeat"));
  
  PR("  rx_channel %u rx_quiesce %u rx_flow_ctrl_dis %u,",
	      val("rx_channel"), val("rx_quiesce"),
	      val("rx_flow_control_disable"));
  PR("  rx_flow_ctrl_ddp %u\n",
	      val("rx_flow_control_ddp"));


  PR("MISCELANEOUS:\n");  /* *************************** */
  PR("  pend_ctl: 0x%1x, unused_flags: 0x%x,  main_slush: 0x%x\n",
	      ((val("pend_ctl2")<<2) | (val("pend_ctl1")<<1) | 
	       val("pend_ctl0")),
	      val("unused"),val("main_slush"));
  PR("  Migrating %u, ask_mode %u, non_offload %u, rss_info %u\n",
	      val("migrating"), 
	      val("ask_mode"), val("non_offload"), val("rss_info"));
  PR("  ULP: ulp_type %u (%s), ulp_raw %u",
	      val("ulp_type"), spr_ulp_type(val("ulp_type")),
	      val("ulp_raw"));


  if (aux==1) {
    PR(",  ulp_ext %u",val("ulp_ext"));
  }
  PR("\n");




  PR("  RDMA: error   %u, flm_err %u\n", 
	      val("rdma_error"), val("rdma_flm_error"));


}
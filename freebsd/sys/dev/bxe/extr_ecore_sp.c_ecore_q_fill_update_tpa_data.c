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
struct tpa_update_ramrod_data {int /*<<< orphan*/  update_ipv6; int /*<<< orphan*/  update_ipv4; int /*<<< orphan*/  tpa_mode; void* sge_pause_thr_low; void* sge_pause_thr_high; void* sge_page_base_lo; void* sge_page_base_hi; void* sge_buff_size; int /*<<< orphan*/  max_tpa_queues; int /*<<< orphan*/  max_sges_for_packet; void* max_agg_size; int /*<<< orphan*/  dont_verify_rings_pause_thr_flg; int /*<<< orphan*/  complete_on_both_clients; int /*<<< orphan*/  client_id; } ;
struct ecore_queue_update_tpa_params {int /*<<< orphan*/  update_ipv6; int /*<<< orphan*/  update_ipv4; int /*<<< orphan*/  tpa_mode; int /*<<< orphan*/  sge_pause_thr_low; int /*<<< orphan*/  sge_pause_thr_high; int /*<<< orphan*/  sge_map; int /*<<< orphan*/  sge_buff_sz; int /*<<< orphan*/  max_tpa_queues; int /*<<< orphan*/  max_sges_pkt; int /*<<< orphan*/  max_agg_sz; int /*<<< orphan*/  dont_verify_thr; int /*<<< orphan*/  complete_on_both_clients; } ;
struct ecore_queue_sp_obj {int /*<<< orphan*/  cl_id; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 void* ECORE_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 void* ECORE_CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_q_fill_update_tpa_data(struct bxe_softc *sc,
				struct ecore_queue_sp_obj *obj,
				struct ecore_queue_update_tpa_params *params,
				struct tpa_update_ramrod_data *data)
{
	data->client_id = obj->cl_id;
	data->complete_on_both_clients = params->complete_on_both_clients;
	data->dont_verify_rings_pause_thr_flg =
		params->dont_verify_thr;
	data->max_agg_size = ECORE_CPU_TO_LE16(params->max_agg_sz);
	data->max_sges_for_packet = params->max_sges_pkt;
	data->max_tpa_queues = params->max_tpa_queues;
	data->sge_buff_size = ECORE_CPU_TO_LE16(params->sge_buff_sz);
	data->sge_page_base_hi = ECORE_CPU_TO_LE32(U64_HI(params->sge_map));
	data->sge_page_base_lo = ECORE_CPU_TO_LE32(U64_LO(params->sge_map));
	data->sge_pause_thr_high = ECORE_CPU_TO_LE16(params->sge_pause_thr_high);
	data->sge_pause_thr_low = ECORE_CPU_TO_LE16(params->sge_pause_thr_low);
	data->tpa_mode = params->tpa_mode;
	data->update_ipv4 = params->update_ipv4;
	data->update_ipv6 = params->update_ipv6;
}
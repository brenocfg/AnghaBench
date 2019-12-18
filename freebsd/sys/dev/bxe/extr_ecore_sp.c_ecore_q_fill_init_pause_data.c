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
struct rxq_pause_params {int /*<<< orphan*/  pri_map; int /*<<< orphan*/  sge_th_hi; int /*<<< orphan*/  sge_th_lo; int /*<<< orphan*/  bd_th_hi; int /*<<< orphan*/  bd_th_lo; int /*<<< orphan*/  rcq_th_hi; int /*<<< orphan*/  rcq_th_lo; } ;
struct ecore_queue_sp_obj {int dummy; } ;
struct client_init_rx_data {void* rx_cos_mask; void* sge_pause_thr_high; void* sge_pause_thr_low; void* bd_pause_thr_high; void* bd_pause_thr_low; void* cqe_pause_thr_high; void* cqe_pause_thr_low; } ;

/* Variables and functions */
 void* ECORE_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_q_fill_init_pause_data(struct ecore_queue_sp_obj *o,
				struct rxq_pause_params *params,
				struct client_init_rx_data *rx_data)
{
	/* flow control data */
	rx_data->cqe_pause_thr_low = ECORE_CPU_TO_LE16(params->rcq_th_lo);
	rx_data->cqe_pause_thr_high = ECORE_CPU_TO_LE16(params->rcq_th_hi);
	rx_data->bd_pause_thr_low = ECORE_CPU_TO_LE16(params->bd_th_lo);
	rx_data->bd_pause_thr_high = ECORE_CPU_TO_LE16(params->bd_th_hi);
	rx_data->sge_pause_thr_low = ECORE_CPU_TO_LE16(params->sge_th_lo);
	rx_data->sge_pause_thr_high = ECORE_CPU_TO_LE16(params->sge_th_hi);
	rx_data->rx_cos_mask = ECORE_CPU_TO_LE16(params->pri_map);
}
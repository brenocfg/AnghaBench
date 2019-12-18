#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  src_qp; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  data_length_error; int /*<<< orphan*/  src_mac_addrlo; int /*<<< orphan*/  src_mac_addrhi; int /*<<< orphan*/  vlan; int /*<<< orphan*/  data_length; TYPE_1__ parse_flags; } ;
union core_rx_cqe_union {TYPE_4__ rx_cqe_gsi; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_length_error; } ;
struct TYPE_6__ {void* data_length; } ;
struct ecore_ll2_comp_rx_data {void* src_qp; void* qp_id; TYPE_3__ u; void* opaque_data_1; void* opaque_data_0; void* vlan; TYPE_2__ length; void* parse_flags; } ;

/* Variables and functions */
 void* OSAL_LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 void* OSAL_LE32_TO_CPU (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ll2_rxq_parse_gsi(union core_rx_cqe_union *p_cqe,
				    struct ecore_ll2_comp_rx_data *data)
{
	data->parse_flags =
		OSAL_LE16_TO_CPU(p_cqe->rx_cqe_gsi.parse_flags.flags);
	data->length.data_length =
		OSAL_LE16_TO_CPU(p_cqe->rx_cqe_gsi.data_length);
	data->vlan =
		OSAL_LE16_TO_CPU(p_cqe->rx_cqe_gsi.vlan);
	data->opaque_data_0 =
		OSAL_LE32_TO_CPU(p_cqe->rx_cqe_gsi.src_mac_addrhi);
	data->opaque_data_1 =
		OSAL_LE16_TO_CPU(p_cqe->rx_cqe_gsi.src_mac_addrlo);
	data->u.data_length_error =
		p_cqe->rx_cqe_gsi.data_length_error;
	data->qp_id = OSAL_LE16_TO_CPU(p_cqe->rx_cqe_gsi.qp_id);

	data->src_qp = OSAL_LE32_TO_CPU(p_cqe->rx_cqe_gsi.src_qp);
}
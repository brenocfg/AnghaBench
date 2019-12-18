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
typedef  int uint64_t ;
struct nicvf {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  NICVF_INTR_CQ 134 
 unsigned long NICVF_INTR_CQ_SHIFT ; 
#define  NICVF_INTR_MBOX 133 
 int NICVF_INTR_MBOX_MASK ; 
#define  NICVF_INTR_PKT_DROP 132 
 int NICVF_INTR_PKT_DROP_MASK ; 
#define  NICVF_INTR_QS_ERR 131 
 int NICVF_INTR_QS_ERR_MASK ; 
#define  NICVF_INTR_RBDR 130 
 unsigned long NICVF_INTR_RBDR_SHIFT ; 
#define  NICVF_INTR_SQ 129 
 unsigned long NICVF_INTR_SQ_SHIFT ; 
#define  NICVF_INTR_TCP_TIMER 128 
 int NICVF_INTR_TCP_TIMER_MASK ; 
 int /*<<< orphan*/  NIC_VF_ENA_W1S ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nicvf_reg_read (struct nicvf*,int /*<<< orphan*/ ) ; 

int
nicvf_is_intr_enabled(struct nicvf *nic, int int_type, int q_idx)
{
	uint64_t reg_val;
	uint64_t mask = 0xff;

	reg_val = nicvf_reg_read(nic, NIC_VF_ENA_W1S);

	switch (int_type) {
	case NICVF_INTR_CQ:
		mask = ((1UL << q_idx) << NICVF_INTR_CQ_SHIFT);
		break;
	case NICVF_INTR_SQ:
		mask = ((1UL << q_idx) << NICVF_INTR_SQ_SHIFT);
		break;
	case NICVF_INTR_RBDR:
		mask = ((1UL << q_idx) << NICVF_INTR_RBDR_SHIFT);
		break;
	case NICVF_INTR_PKT_DROP:
		mask = NICVF_INTR_PKT_DROP_MASK;
		break;
	case NICVF_INTR_TCP_TIMER:
		mask = NICVF_INTR_TCP_TIMER_MASK;
		break;
	case NICVF_INTR_MBOX:
		mask = NICVF_INTR_MBOX_MASK;
		break;
	case NICVF_INTR_QS_ERR:
		mask = NICVF_INTR_QS_ERR_MASK;
		break;
	default:
		device_printf(nic->dev,
			   "Failed to check interrupt enable: unknown type\n");
		break;
	}

	return (reg_val & mask);
}
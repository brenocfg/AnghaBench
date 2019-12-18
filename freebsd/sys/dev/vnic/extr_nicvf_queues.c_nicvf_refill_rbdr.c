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
struct rbdr_entry_t {int buf_addr; } ;
struct TYPE_2__ {int q_len; } ;
struct rbdr {int idx; int /*<<< orphan*/ * rbdr_buff_dmaps; TYPE_1__ dmem; int /*<<< orphan*/  enable; struct nicvf* nic; } ;
struct queue_set {int rbdr_len; } ;
struct nicvf {struct queue_set* qs; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int bus_addr_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 struct rbdr_entry_t* GET_RBDR_DESC (struct rbdr*,int) ; 
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int NICVF_RCV_BUF_ALIGN ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_DOOR ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_STATUS0 ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_TAIL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ nicvf_alloc_rcv_buffer (struct nicvf*,struct rbdr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
nicvf_refill_rbdr(struct rbdr *rbdr, int mflags)
{
	struct nicvf *nic;
	struct queue_set *qs;
	int rbdr_idx;
	int tail, qcount;
	int refill_rb_cnt;
	struct rbdr_entry_t *desc;
	bus_dmamap_t dmap;
	bus_addr_t rbuf;
	boolean_t rb_alloc_fail;
	int new_rb;

	rb_alloc_fail = TRUE;
	new_rb = 0;
	nic = rbdr->nic;
	qs = nic->qs;
	rbdr_idx = rbdr->idx;

	/* Check if it's enabled */
	if (!rbdr->enable)
		return (0);

	/* Get no of desc's to be refilled */
	qcount = nicvf_queue_reg_read(nic, NIC_QSET_RBDR_0_1_STATUS0, rbdr_idx);
	qcount &= 0x7FFFF;
	/* Doorbell can be ringed with a max of ring size minus 1 */
	if (qcount >= (qs->rbdr_len - 1)) {
		rb_alloc_fail = FALSE;
		goto out;
	} else
		refill_rb_cnt = qs->rbdr_len - qcount - 1;

	/* Start filling descs from tail */
	tail = nicvf_queue_reg_read(nic, NIC_QSET_RBDR_0_1_TAIL, rbdr_idx) >> 3;
	while (refill_rb_cnt) {
		tail++;
		tail &= (rbdr->dmem.q_len - 1);

		dmap = rbdr->rbdr_buff_dmaps[tail];
		if (nicvf_alloc_rcv_buffer(nic, rbdr, dmap, mflags,
		    DMA_BUFFER_LEN, &rbuf)) {
			/* Something went wrong. Resign */
			break;
		}
		desc = GET_RBDR_DESC(rbdr, tail);
		desc->buf_addr = (rbuf >> NICVF_RCV_BUF_ALIGN);
		refill_rb_cnt--;
		new_rb++;
	}

	/* make sure all memory stores are done before ringing doorbell */
	wmb();

	/* Check if buffer allocation failed */
	if (refill_rb_cnt == 0)
		rb_alloc_fail = FALSE;

	/* Notify HW */
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_DOOR,
			      rbdr_idx, new_rb);
out:
	if (!rb_alloc_fail) {
		/*
		 * Re-enable RBDR interrupts only
		 * if buffer allocation is success.
		 */
		nicvf_enable_intr(nic, NICVF_INTR_RBDR, rbdr_idx);

		return (0);
	}

	return (ENOMEM);
}
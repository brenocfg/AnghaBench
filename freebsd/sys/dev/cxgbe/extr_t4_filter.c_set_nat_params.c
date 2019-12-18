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
struct TYPE_2__ {int* nat_dip; int* nat_sip; int nat_dport; int nat_sport; scalar_t__ type; } ;
struct filter_entry {TYPE_1__ fs; int /*<<< orphan*/  tid; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORD_MASK ; 
 scalar_t__ W_TCB_PDU_HDR_LEN ; 
 scalar_t__ W_TCB_RX_FRAG2_PTR_RAW ; 
 scalar_t__ W_TCB_RX_FRAG3_LEN_RAW ; 
 scalar_t__ W_TCB_RX_FRAG3_START_IDX_OFFSET_RAW ; 
 scalar_t__ W_TCB_SND_UNA_RAW ; 
 int /*<<< orphan*/  set_tcb_field (struct adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
set_nat_params(struct adapter *sc, struct filter_entry *f, const bool dip,
    const bool sip, const bool dp, const bool sp)
{

	if (dip) {
		if (f->fs.type) {
			set_tcb_field(sc, f->tid, W_TCB_SND_UNA_RAW, WORD_MASK,
			    f->fs.nat_dip[15] | f->fs.nat_dip[14] << 8 |
			    f->fs.nat_dip[13] << 16 | f->fs.nat_dip[12] << 24, 1);

			set_tcb_field(sc, f->tid,
			    W_TCB_SND_UNA_RAW + 1, WORD_MASK,
			    f->fs.nat_dip[11] | f->fs.nat_dip[10] << 8 |
			    f->fs.nat_dip[9] << 16 | f->fs.nat_dip[8] << 24, 1);

			set_tcb_field(sc, f->tid,
			    W_TCB_SND_UNA_RAW + 2, WORD_MASK,
			    f->fs.nat_dip[7] | f->fs.nat_dip[6] << 8 |
			    f->fs.nat_dip[5] << 16 | f->fs.nat_dip[4] << 24, 1);

			set_tcb_field(sc, f->tid,
			    W_TCB_SND_UNA_RAW + 3, WORD_MASK,
			    f->fs.nat_dip[3] | f->fs.nat_dip[2] << 8 |
			    f->fs.nat_dip[1] << 16 | f->fs.nat_dip[0] << 24, 1);
		} else {
			set_tcb_field(sc, f->tid,
			    W_TCB_RX_FRAG3_LEN_RAW, WORD_MASK,
			    f->fs.nat_dip[3] | f->fs.nat_dip[2] << 8 |
			    f->fs.nat_dip[1] << 16 | f->fs.nat_dip[0] << 24, 1);
		}
	}

	if (sip) {
		if (f->fs.type) {
			set_tcb_field(sc, f->tid,
			    W_TCB_RX_FRAG2_PTR_RAW, WORD_MASK,
			    f->fs.nat_sip[15] | f->fs.nat_sip[14] << 8 |
			    f->fs.nat_sip[13] << 16 | f->fs.nat_sip[12] << 24, 1);

			set_tcb_field(sc, f->tid,
			    W_TCB_RX_FRAG2_PTR_RAW + 1, WORD_MASK,
			    f->fs.nat_sip[11] | f->fs.nat_sip[10] << 8 |
			    f->fs.nat_sip[9] << 16 | f->fs.nat_sip[8] << 24, 1);

			set_tcb_field(sc, f->tid,
			    W_TCB_RX_FRAG2_PTR_RAW + 2, WORD_MASK,
			    f->fs.nat_sip[7] | f->fs.nat_sip[6] << 8 |
			    f->fs.nat_sip[5] << 16 | f->fs.nat_sip[4] << 24, 1);

			set_tcb_field(sc, f->tid,
			    W_TCB_RX_FRAG2_PTR_RAW + 3, WORD_MASK,
			    f->fs.nat_sip[3] | f->fs.nat_sip[2] << 8 |
			    f->fs.nat_sip[1] << 16 | f->fs.nat_sip[0] << 24, 1);

		} else {
			set_tcb_field(sc, f->tid,
			    W_TCB_RX_FRAG3_START_IDX_OFFSET_RAW, WORD_MASK,
			    f->fs.nat_sip[3] | f->fs.nat_sip[2] << 8 |
			    f->fs.nat_sip[1] << 16 | f->fs.nat_sip[0] << 24, 1);
		}
	}

	set_tcb_field(sc, f->tid, W_TCB_PDU_HDR_LEN, WORD_MASK,
	    (dp ? f->fs.nat_dport : 0) | (sp ? f->fs.nat_sport << 16 : 0), 1);
}
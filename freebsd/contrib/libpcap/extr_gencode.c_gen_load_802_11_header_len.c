#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int k; struct slist* jf; struct slist* jt; } ;
struct slist {TYPE_3__ s; } ;
struct TYPE_8__ {int reg; } ;
struct TYPE_7__ {int constant_part; } ;
struct TYPE_10__ {int no_optimize; scalar_t__ linktype; TYPE_2__ off_linkpl; TYPE_1__ off_outermostlinkhdr; } ;
typedef  TYPE_4__ compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int BPF_ADD ; 
 int BPF_ALU ; 
 int BPF_AND ; 
 int BPF_B ; 
 int BPF_IMM ; 
 int BPF_IND ; 
 int /*<<< orphan*/  BPF_JSET ; 
 int BPF_K ; 
 int BPF_LD ; 
 int BPF_LDX ; 
 int BPF_MEM ; 
 int BPF_MISC ; 
 int BPF_ST ; 
 int BPF_TXA ; 
 int BPF_W ; 
 scalar_t__ DLT_IEEE802_11_RADIO ; 
 int JMP (int /*<<< orphan*/ ) ; 
 void* SWAPLONG (int) ; 
 struct slist* new_stmt (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct slist *
gen_load_802_11_header_len(compiler_state_t *cstate, struct slist *s, struct slist *snext)
{
	struct slist *s2;
	struct slist *sjset_data_frame_1;
	struct slist *sjset_data_frame_2;
	struct slist *sjset_qos;
	struct slist *sjset_radiotap_flags_present;
	struct slist *sjset_radiotap_ext_present;
	struct slist *sjset_radiotap_tsft_present;
	struct slist *sjset_tsft_datapad, *sjset_notsft_datapad;
	struct slist *s_roundup;

	if (cstate->off_linkpl.reg == -1) {
		/*
		 * No register has been assigned to the offset of
		 * the link-layer payload, which means nobody needs
		 * it; don't bother computing it - just return
		 * what we already have.
		 */
		return (s);
	}

	/*
	 * This code is not compatible with the optimizer, as
	 * we are generating jmp instructions within a normal
	 * slist of instructions
	 */
	cstate->no_optimize = 1;

	/*
	 * If "s" is non-null, it has code to arrange that the X register
	 * contains the length of the prefix preceding the link-layer
	 * header.
	 *
	 * Otherwise, the length of the prefix preceding the link-layer
	 * header is "off_outermostlinkhdr.constant_part".
	 */
	if (s == NULL) {
		/*
		 * There is no variable-length header preceding the
		 * link-layer header.
		 *
		 * Load the length of the fixed-length prefix preceding
		 * the link-layer header (if any) into the X register,
		 * and store it in the cstate->off_linkpl.reg register.
		 * That length is off_outermostlinkhdr.constant_part.
		 */
		s = new_stmt(cstate, BPF_LDX|BPF_IMM);
		s->s.k = cstate->off_outermostlinkhdr.constant_part;
	}

	/*
	 * The X register contains the offset of the beginning of the
	 * link-layer header; add 24, which is the minimum length
	 * of the MAC header for a data frame, to that, and store it
	 * in cstate->off_linkpl.reg, and then load the Frame Control field,
	 * which is at the offset in the X register, with an indexed load.
	 */
	s2 = new_stmt(cstate, BPF_MISC|BPF_TXA);
	sappend(s, s2);
	s2 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s2->s.k = 24;
	sappend(s, s2);
	s2 = new_stmt(cstate, BPF_ST);
	s2->s.k = cstate->off_linkpl.reg;
	sappend(s, s2);

	s2 = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
	s2->s.k = 0;
	sappend(s, s2);

	/*
	 * Check the Frame Control field to see if this is a data frame;
	 * a data frame has the 0x08 bit (b3) in that field set and the
	 * 0x04 bit (b2) clear.
	 */
	sjset_data_frame_1 = new_stmt(cstate, JMP(BPF_JSET));
	sjset_data_frame_1->s.k = 0x08;
	sappend(s, sjset_data_frame_1);

	/*
	 * If b3 is set, test b2, otherwise go to the first statement of
	 * the rest of the program.
	 */
	sjset_data_frame_1->s.jt = sjset_data_frame_2 = new_stmt(cstate, JMP(BPF_JSET));
	sjset_data_frame_2->s.k = 0x04;
	sappend(s, sjset_data_frame_2);
	sjset_data_frame_1->s.jf = snext;

	/*
	 * If b2 is not set, this is a data frame; test the QoS bit.
	 * Otherwise, go to the first statement of the rest of the
	 * program.
	 */
	sjset_data_frame_2->s.jt = snext;
	sjset_data_frame_2->s.jf = sjset_qos = new_stmt(cstate, JMP(BPF_JSET));
	sjset_qos->s.k = 0x80;	/* QoS bit */
	sappend(s, sjset_qos);

	/*
	 * If it's set, add 2 to cstate->off_linkpl.reg, to skip the QoS
	 * field.
	 * Otherwise, go to the first statement of the rest of the
	 * program.
	 */
	sjset_qos->s.jt = s2 = new_stmt(cstate, BPF_LD|BPF_MEM);
	s2->s.k = cstate->off_linkpl.reg;
	sappend(s, s2);
	s2 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_IMM);
	s2->s.k = 2;
	sappend(s, s2);
	s2 = new_stmt(cstate, BPF_ST);
	s2->s.k = cstate->off_linkpl.reg;
	sappend(s, s2);

	/*
	 * If we have a radiotap header, look at it to see whether
	 * there's Atheros padding between the MAC-layer header
	 * and the payload.
	 *
	 * Note: all of the fields in the radiotap header are
	 * little-endian, so we byte-swap all of the values
	 * we test against, as they will be loaded as big-endian
	 * values.
	 *
	 * XXX - in the general case, we would have to scan through
	 * *all* the presence bits, if there's more than one word of
	 * presence bits.  That would require a loop, meaning that
	 * we wouldn't be able to run the filter in the kernel.
	 *
	 * We assume here that the Atheros adapters that insert the
	 * annoying padding don't have multiple antennae and therefore
	 * do not generate radiotap headers with multiple presence words.
	 */
	if (cstate->linktype == DLT_IEEE802_11_RADIO) {
		/*
		 * Is the IEEE80211_RADIOTAP_FLAGS bit (0x0000002) set
		 * in the first presence flag word?
		 */
		sjset_qos->s.jf = s2 = new_stmt(cstate, BPF_LD|BPF_ABS|BPF_W);
		s2->s.k = 4;
		sappend(s, s2);

		sjset_radiotap_flags_present = new_stmt(cstate, JMP(BPF_JSET));
		sjset_radiotap_flags_present->s.k = SWAPLONG(0x00000002);
		sappend(s, sjset_radiotap_flags_present);

		/*
		 * If not, skip all of this.
		 */
		sjset_radiotap_flags_present->s.jf = snext;

		/*
		 * Otherwise, is the "extension" bit set in that word?
		 */
		sjset_radiotap_ext_present = new_stmt(cstate, JMP(BPF_JSET));
		sjset_radiotap_ext_present->s.k = SWAPLONG(0x80000000);
		sappend(s, sjset_radiotap_ext_present);
		sjset_radiotap_flags_present->s.jt = sjset_radiotap_ext_present;

		/*
		 * If so, skip all of this.
		 */
		sjset_radiotap_ext_present->s.jt = snext;

		/*
		 * Otherwise, is the IEEE80211_RADIOTAP_TSFT bit set?
		 */
		sjset_radiotap_tsft_present = new_stmt(cstate, JMP(BPF_JSET));
		sjset_radiotap_tsft_present->s.k = SWAPLONG(0x00000001);
		sappend(s, sjset_radiotap_tsft_present);
		sjset_radiotap_ext_present->s.jf = sjset_radiotap_tsft_present;

		/*
		 * If IEEE80211_RADIOTAP_TSFT is set, the flags field is
		 * at an offset of 16 from the beginning of the raw packet
		 * data (8 bytes for the radiotap header and 8 bytes for
		 * the TSFT field).
		 *
		 * Test whether the IEEE80211_RADIOTAP_F_DATAPAD bit (0x20)
		 * is set.
		 */
		s2 = new_stmt(cstate, BPF_LD|BPF_ABS|BPF_B);
		s2->s.k = 16;
		sappend(s, s2);
		sjset_radiotap_tsft_present->s.jt = s2;

		sjset_tsft_datapad = new_stmt(cstate, JMP(BPF_JSET));
		sjset_tsft_datapad->s.k = 0x20;
		sappend(s, sjset_tsft_datapad);

		/*
		 * If IEEE80211_RADIOTAP_TSFT is not set, the flags field is
		 * at an offset of 8 from the beginning of the raw packet
		 * data (8 bytes for the radiotap header).
		 *
		 * Test whether the IEEE80211_RADIOTAP_F_DATAPAD bit (0x20)
		 * is set.
		 */
		s2 = new_stmt(cstate, BPF_LD|BPF_ABS|BPF_B);
		s2->s.k = 8;
		sappend(s, s2);
		sjset_radiotap_tsft_present->s.jf = s2;

		sjset_notsft_datapad = new_stmt(cstate, JMP(BPF_JSET));
		sjset_notsft_datapad->s.k = 0x20;
		sappend(s, sjset_notsft_datapad);

		/*
		 * In either case, if IEEE80211_RADIOTAP_F_DATAPAD is
		 * set, round the length of the 802.11 header to
		 * a multiple of 4.  Do that by adding 3 and then
		 * dividing by and multiplying by 4, which we do by
		 * ANDing with ~3.
		 */
		s_roundup = new_stmt(cstate, BPF_LD|BPF_MEM);
		s_roundup->s.k = cstate->off_linkpl.reg;
		sappend(s, s_roundup);
		s2 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_IMM);
		s2->s.k = 3;
		sappend(s, s2);
		s2 = new_stmt(cstate, BPF_ALU|BPF_AND|BPF_IMM);
		s2->s.k = ~3;
		sappend(s, s2);
		s2 = new_stmt(cstate, BPF_ST);
		s2->s.k = cstate->off_linkpl.reg;
		sappend(s, s2);

		sjset_tsft_datapad->s.jt = s_roundup;
		sjset_tsft_datapad->s.jf = snext;
		sjset_notsft_datapad->s.jt = s_roundup;
		sjset_notsft_datapad->s.jf = snext;
	} else
		sjset_qos->s.jf = snext;

	return s;
}
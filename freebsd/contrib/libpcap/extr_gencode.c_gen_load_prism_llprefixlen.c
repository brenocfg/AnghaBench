#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int k; struct slist* jf; struct slist* jt; } ;
struct slist {TYPE_2__ s; } ;
struct TYPE_6__ {int reg; } ;
struct TYPE_8__ {int no_optimize; TYPE_1__ off_linkhdr; } ;
typedef  TYPE_3__ compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int BPF_ALU ; 
 int BPF_AND ; 
 int BPF_IMM ; 
 int /*<<< orphan*/  BPF_JA ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_K ; 
 int BPF_LD ; 
 int BPF_MISC ; 
 int BPF_ST ; 
 int BPF_TAX ; 
 int BPF_W ; 
 int JMP (int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct slist *
gen_load_prism_llprefixlen(compiler_state_t *cstate)
{
	struct slist *s1, *s2;
	struct slist *sjeq_avs_cookie;
	struct slist *sjcommon;

	/*
	 * This code is not compatible with the optimizer, as
	 * we are generating jmp instructions within a normal
	 * slist of instructions
	 */
	cstate->no_optimize = 1;

	/*
	 * Generate code to load the length of the radio header into
	 * the register assigned to hold that length, if one has been
	 * assigned.  (If one hasn't been assigned, no code we've
	 * generated uses that prefix, so we don't need to generate any
	 * code to load it.)
	 *
	 * Some Linux drivers use ARPHRD_IEEE80211_PRISM but sometimes
	 * or always use the AVS header rather than the Prism header.
	 * We load a 4-byte big-endian value at the beginning of the
	 * raw packet data, and see whether, when masked with 0xFFFFF000,
	 * it's equal to 0x80211000.  If so, that indicates that it's
	 * an AVS header (the masked-out bits are the version number).
	 * Otherwise, it's a Prism header.
	 *
	 * XXX - the Prism header is also, in theory, variable-length,
	 * but no known software generates headers that aren't 144
	 * bytes long.
	 */
	if (cstate->off_linkhdr.reg != -1) {
		/*
		 * Load the cookie.
		 */
		s1 = new_stmt(cstate, BPF_LD|BPF_W|BPF_ABS);
		s1->s.k = 0;

		/*
		 * AND it with 0xFFFFF000.
		 */
		s2 = new_stmt(cstate, BPF_ALU|BPF_AND|BPF_K);
		s2->s.k = 0xFFFFF000;
		sappend(s1, s2);

		/*
		 * Compare with 0x80211000.
		 */
		sjeq_avs_cookie = new_stmt(cstate, JMP(BPF_JEQ));
		sjeq_avs_cookie->s.k = 0x80211000;
		sappend(s1, sjeq_avs_cookie);

		/*
		 * If it's AVS:
		 *
		 * The 4 bytes at an offset of 4 from the beginning of
		 * the AVS header are the length of the AVS header.
		 * That field is big-endian.
		 */
		s2 = new_stmt(cstate, BPF_LD|BPF_W|BPF_ABS);
		s2->s.k = 4;
		sappend(s1, s2);
		sjeq_avs_cookie->s.jt = s2;

		/*
		 * Now jump to the code to allocate a register
		 * into which to save the header length and
		 * store the length there.  (The "jump always"
		 * instruction needs to have the k field set;
		 * it's added to the PC, so, as we're jumping
		 * over a single instruction, it should be 1.)
		 */
		sjcommon = new_stmt(cstate, JMP(BPF_JA));
		sjcommon->s.k = 1;
		sappend(s1, sjcommon);

		/*
		 * Now for the code that handles the Prism header.
		 * Just load the length of the Prism header (144)
		 * into the A register.  Have the test for an AVS
		 * header branch here if we don't have an AVS header.
		 */
		s2 = new_stmt(cstate, BPF_LD|BPF_W|BPF_IMM);
		s2->s.k = 144;
		sappend(s1, s2);
		sjeq_avs_cookie->s.jf = s2;

		/*
		 * Now allocate a register to hold that value and store
		 * it.  The code for the AVS header will jump here after
		 * loading the length of the AVS header.
		 */
		s2 = new_stmt(cstate, BPF_ST);
		s2->s.k = cstate->off_linkhdr.reg;
		sappend(s1, s2);
		sjcommon->s.jf = s2;

		/*
		 * Now move it into the X register.
		 */
		s2 = new_stmt(cstate, BPF_MISC|BPF_TAX);
		sappend(s1, s2);

		return (s1);
	} else
		return (NULL);
}
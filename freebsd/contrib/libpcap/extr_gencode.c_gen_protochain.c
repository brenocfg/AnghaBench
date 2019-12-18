#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int k; struct slist* jt; struct slist* jf; } ;
struct slist {struct slist* next; TYPE_2__ s; } ;
struct TYPE_15__ {int k; } ;
struct block {TYPE_3__ s; struct slist* stmts; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_13__ {int constant_part; scalar_t__ is_variable; } ;
struct TYPE_16__ {int no_optimize; int off_nl; TYPE_1__ off_linkpl; } ;
typedef  TYPE_4__ compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int BPF_ADD ; 
 int BPF_ALU ; 
 int BPF_B ; 
 int BPF_IMM ; 
 int BPF_IND ; 
 int BPF_JA ; 
 int BPF_JEQ ; 
 int BPF_JMP ; 
 int BPF_K ; 
 int BPF_LD ; 
 int BPF_LDX ; 
 int BPF_MEM ; 
 int BPF_MISC ; 
 int BPF_MSH ; 
 int BPF_MUL ; 
 int BPF_ST ; 
 int BPF_TAX ; 
 int BPF_TXA ; 
 int BPF_X ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int /*<<< orphan*/  ETHERTYPE_IPV6 ; 
 int IPPROTO_AH ; 
 int IPPROTO_DSTOPTS ; 
 int IPPROTO_FRAGMENT ; 
 int IPPROTO_HOPOPTS ; 
 int IPPROTO_NONE ; 
 int IPPROTO_ROUTING ; 
 int /*<<< orphan*/  JMP (int) ; 
#define  Q_DEFAULT 130 
#define  Q_IP 129 
#define  Q_IPV6 128 
 int alloc_reg (TYPE_4__*) ; 
 int /*<<< orphan*/  bpf_error (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  free_reg (TYPE_4__*,int) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_linktype (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_proto (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/  memset (struct slist**,int /*<<< orphan*/ ,int) ; 
 struct block* new_block (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (TYPE_4__*,int) ; 

__attribute__((used)) static struct block *
gen_protochain(compiler_state_t *cstate, int v, int proto, int dir)
{
#ifdef NO_PROTOCHAIN
	return gen_proto(cstate, v, proto, dir);
#else
	struct block *b0, *b;
	struct slist *s[100];
	int fix2, fix3, fix4, fix5;
	int ahcheck, again, end;
	int i, max;
	int reg2 = alloc_reg(cstate);

	memset(s, 0, sizeof(s));
	fix3 = fix4 = fix5 = 0;

	switch (proto) {
	case Q_IP:
	case Q_IPV6:
		break;
	case Q_DEFAULT:
		b0 = gen_protochain(cstate, v, Q_IP, dir);
		b = gen_protochain(cstate, v, Q_IPV6, dir);
		gen_or(b0, b);
		return b;
	default:
		bpf_error(cstate, "bad protocol applied for 'protochain'");
		/*NOTREACHED*/
	}

	/*
	 * We don't handle variable-length prefixes before the link-layer
	 * header, or variable-length link-layer headers, here yet.
	 * We might want to add BPF instructions to do the protochain
	 * work, to simplify that and, on platforms that have a BPF
	 * interpreter with the new instructions, let the filtering
	 * be done in the kernel.  (We already require a modified BPF
	 * engine to do the protochain stuff, to support backward
	 * branches, and backward branch support is unlikely to appear
	 * in kernel BPF engines.)
	 */
	if (cstate->off_linkpl.is_variable)
		bpf_error(cstate, "'protochain' not supported with variable length headers");

	cstate->no_optimize = 1; /* this code is not compatible with optimizer yet */

	/*
	 * s[0] is a dummy entry to protect other BPF insn from damage
	 * by s[fix] = foo with uninitialized variable "fix".  It is somewhat
	 * hard to find interdependency made by jump table fixup.
	 */
	i = 0;
	s[i] = new_stmt(cstate, 0);	/*dummy*/
	i++;

	switch (proto) {
	case Q_IP:
		b0 = gen_linktype(cstate, ETHERTYPE_IP);

		/* A = ip->ip_p */
		s[i] = new_stmt(cstate, BPF_LD|BPF_ABS|BPF_B);
		s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl + 9;
		i++;
		/* X = ip->ip_hl << 2 */
		s[i] = new_stmt(cstate, BPF_LDX|BPF_MSH|BPF_B);
		s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
		i++;
		break;

	case Q_IPV6:
		b0 = gen_linktype(cstate, ETHERTYPE_IPV6);

		/* A = ip6->ip_nxt */
		s[i] = new_stmt(cstate, BPF_LD|BPF_ABS|BPF_B);
		s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl + 6;
		i++;
		/* X = sizeof(struct ip6_hdr) */
		s[i] = new_stmt(cstate, BPF_LDX|BPF_IMM);
		s[i]->s.k = 40;
		i++;
		break;

	default:
		bpf_error(cstate, "unsupported proto to gen_protochain");
		/*NOTREACHED*/
	}

	/* again: if (A == v) goto end; else fall through; */
	again = i;
	s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
	s[i]->s.k = v;
	s[i]->s.jt = NULL;		/*later*/
	s[i]->s.jf = NULL;		/*update in next stmt*/
	fix5 = i;
	i++;

#ifndef IPPROTO_NONE
#define IPPROTO_NONE	59
#endif
	/* if (A == IPPROTO_NONE) goto end */
	s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
	s[i]->s.jt = NULL;	/*later*/
	s[i]->s.jf = NULL;	/*update in next stmt*/
	s[i]->s.k = IPPROTO_NONE;
	s[fix5]->s.jf = s[i];
	fix2 = i;
	i++;

	if (proto == Q_IPV6) {
		int v6start, v6end, v6advance, j;

		v6start = i;
		/* if (A == IPPROTO_HOPOPTS) goto v6advance */
		s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
		s[i]->s.jt = NULL;	/*later*/
		s[i]->s.jf = NULL;	/*update in next stmt*/
		s[i]->s.k = IPPROTO_HOPOPTS;
		s[fix2]->s.jf = s[i];
		i++;
		/* if (A == IPPROTO_DSTOPTS) goto v6advance */
		s[i - 1]->s.jf = s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
		s[i]->s.jt = NULL;	/*later*/
		s[i]->s.jf = NULL;	/*update in next stmt*/
		s[i]->s.k = IPPROTO_DSTOPTS;
		i++;
		/* if (A == IPPROTO_ROUTING) goto v6advance */
		s[i - 1]->s.jf = s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
		s[i]->s.jt = NULL;	/*later*/
		s[i]->s.jf = NULL;	/*update in next stmt*/
		s[i]->s.k = IPPROTO_ROUTING;
		i++;
		/* if (A == IPPROTO_FRAGMENT) goto v6advance; else goto ahcheck; */
		s[i - 1]->s.jf = s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
		s[i]->s.jt = NULL;	/*later*/
		s[i]->s.jf = NULL;	/*later*/
		s[i]->s.k = IPPROTO_FRAGMENT;
		fix3 = i;
		v6end = i;
		i++;

		/* v6advance: */
		v6advance = i;

		/*
		 * in short,
		 * A = P[X + packet head];
		 * X = X + (P[X + packet head + 1] + 1) * 8;
		 */
		/* A = P[X + packet head] */
		s[i] = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
		s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
		i++;
		/* MEM[reg2] = A */
		s[i] = new_stmt(cstate, BPF_ST);
		s[i]->s.k = reg2;
		i++;
		/* A = P[X + packet head + 1]; */
		s[i] = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
		s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl + 1;
		i++;
		/* A += 1 */
		s[i] = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
		s[i]->s.k = 1;
		i++;
		/* A *= 8 */
		s[i] = new_stmt(cstate, BPF_ALU|BPF_MUL|BPF_K);
		s[i]->s.k = 8;
		i++;
		/* A += X */
		s[i] = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X);
		s[i]->s.k = 0;
		i++;
		/* X = A; */
		s[i] = new_stmt(cstate, BPF_MISC|BPF_TAX);
		i++;
		/* A = MEM[reg2] */
		s[i] = new_stmt(cstate, BPF_LD|BPF_MEM);
		s[i]->s.k = reg2;
		i++;

		/* goto again; (must use BPF_JA for backward jump) */
		s[i] = new_stmt(cstate, BPF_JMP|BPF_JA);
		s[i]->s.k = again - i - 1;
		s[i - 1]->s.jf = s[i];
		i++;

		/* fixup */
		for (j = v6start; j <= v6end; j++)
			s[j]->s.jt = s[v6advance];
	} else {
		/* nop */
		s[i] = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
		s[i]->s.k = 0;
		s[fix2]->s.jf = s[i];
		i++;
	}

	/* ahcheck: */
	ahcheck = i;
	/* if (A == IPPROTO_AH) then fall through; else goto end; */
	s[i] = new_stmt(cstate, BPF_JMP|BPF_JEQ|BPF_K);
	s[i]->s.jt = NULL;	/*later*/
	s[i]->s.jf = NULL;	/*later*/
	s[i]->s.k = IPPROTO_AH;
	if (fix3)
		s[fix3]->s.jf = s[ahcheck];
	fix4 = i;
	i++;

	/*
	 * in short,
	 * A = P[X];
	 * X = X + (P[X + 1] + 2) * 4;
	 */
	/* A = X */
	s[i - 1]->s.jt = s[i] = new_stmt(cstate, BPF_MISC|BPF_TXA);
	i++;
	/* A = P[X + packet head]; */
	s[i] = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
	s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
	i++;
	/* MEM[reg2] = A */
	s[i] = new_stmt(cstate, BPF_ST);
	s[i]->s.k = reg2;
	i++;
	/* A = X */
	s[i - 1]->s.jt = s[i] = new_stmt(cstate, BPF_MISC|BPF_TXA);
	i++;
	/* A += 1 */
	s[i] = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s[i]->s.k = 1;
	i++;
	/* X = A */
	s[i] = new_stmt(cstate, BPF_MISC|BPF_TAX);
	i++;
	/* A = P[X + packet head] */
	s[i] = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
	s[i]->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
	i++;
	/* A += 2 */
	s[i] = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s[i]->s.k = 2;
	i++;
	/* A *= 4 */
	s[i] = new_stmt(cstate, BPF_ALU|BPF_MUL|BPF_K);
	s[i]->s.k = 4;
	i++;
	/* X = A; */
	s[i] = new_stmt(cstate, BPF_MISC|BPF_TAX);
	i++;
	/* A = MEM[reg2] */
	s[i] = new_stmt(cstate, BPF_LD|BPF_MEM);
	s[i]->s.k = reg2;
	i++;

	/* goto again; (must use BPF_JA for backward jump) */
	s[i] = new_stmt(cstate, BPF_JMP|BPF_JA);
	s[i]->s.k = again - i - 1;
	i++;

	/* end: nop */
	end = i;
	s[i] = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s[i]->s.k = 0;
	s[fix2]->s.jt = s[end];
	s[fix4]->s.jf = s[end];
	s[fix5]->s.jt = s[end];
	i++;

	/*
	 * make slist chain
	 */
	max = i;
	for (i = 0; i < max - 1; i++)
		s[i]->next = s[i + 1];
	s[max - 1]->next = NULL;

	/*
	 * emit final check
	 */
	b = new_block(cstate, JMP(BPF_JEQ));
	b->stmts = s[1];	/*remember, s[0] is dummy*/
	b->s.k = v;

	free_reg(cstate, reg2);

	gen_and(b0, b);
	return b;
#endif
}
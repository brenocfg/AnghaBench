#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ k; } ;
struct slist {TYPE_1__ s; } ;
struct TYPE_4__ {int k; } ;
struct block {TYPE_2__ s; struct slist* stmts; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int BPF_B ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_LD ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 scalar_t__ SKF_AD_OFF ; 
 scalar_t__ SKF_AD_VLAN_TAG_PRESENT ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 int /*<<< orphan*/  gen_vlan_patch_tpid_test (int /*<<< orphan*/ *,struct block*) ; 
 int /*<<< orphan*/  gen_vlan_patch_vid_test (int /*<<< orphan*/ *,struct block*) ; 
 struct block* gen_vlan_tpid_test (int /*<<< orphan*/ *) ; 
 struct block* gen_vlan_vid_test (int /*<<< orphan*/ *,int) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct block *
gen_vlan_bpf_extensions(compiler_state_t *cstate, int vlan_num)
{
        struct block *b0, *b_tpid, *b_vid = NULL;
        struct slist *s;

        /* generate new filter code based on extracting packet
         * metadata */
        s = new_stmt(cstate, BPF_LD|BPF_B|BPF_ABS);
        s->s.k = SKF_AD_OFF + SKF_AD_VLAN_TAG_PRESENT;

        b0 = new_block(cstate, JMP(BPF_JEQ));
        b0->stmts = s;
        b0->s.k = 1;

	/*
	 * This is tricky. We need to insert the statements updating variable
	 * parts of offsets before the the traditional TPID and VID tests so
	 * that they are called whenever SKF_AD_VLAN_TAG_PRESENT fails but
	 * we do not want this update to affect those checks. That's why we
	 * generate both test blocks first and insert the statements updating
	 * variable parts of both offsets after that. This wouldn't work if
	 * there already were variable length link header when entering this
	 * function but gen_vlan_bpf_extensions() isn't called in that case.
	 */
	b_tpid = gen_vlan_tpid_test(cstate);
	if (vlan_num >= 0)
		b_vid = gen_vlan_vid_test(cstate, vlan_num);

	gen_vlan_patch_tpid_test(cstate, b_tpid);
	gen_or(b0, b_tpid);
	b0 = b_tpid;

	if (vlan_num >= 0) {
		gen_vlan_patch_vid_test(cstate, b_vid);
		gen_and(b0, b_vid);
		b0 = b_vid;
	}

        return b0;
}
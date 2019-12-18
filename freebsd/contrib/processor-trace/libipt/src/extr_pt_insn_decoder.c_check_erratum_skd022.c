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
struct pt_insn_ext {int iclass; } ;
struct pt_insn_decoder {int /*<<< orphan*/  asid; int /*<<< orphan*/  image; int /*<<< orphan*/  ip; int /*<<< orphan*/  mode; } ;
struct pt_insn {int /*<<< orphan*/  ip; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  PTI_INST_VMLAUNCH 129 
#define  PTI_INST_VMRESUME 128 
 int pt_insn_decode (struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pte_internal ; 

__attribute__((used)) static int check_erratum_skd022(struct pt_insn_decoder *decoder)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;
	int errcode;

	if (!decoder)
		return -pte_internal;

	insn.mode = decoder->mode;
	insn.ip = decoder->ip;

	errcode = pt_insn_decode(&insn, &iext, decoder->image, &decoder->asid);
	if (errcode < 0)
		return 0;

	switch (iext.iclass) {
	default:
		return 0;

	case PTI_INST_VMLAUNCH:
	case PTI_INST_VMRESUME:
		return 1;
	}
}
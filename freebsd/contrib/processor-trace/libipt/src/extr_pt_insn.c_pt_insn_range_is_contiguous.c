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
typedef  scalar_t__ uint64_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int mode; scalar_t__ ip; } ;
struct pt_image {int dummy; } ;
struct pt_asid {int dummy; } ;
typedef  int /*<<< orphan*/  insn ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_insn*,int /*<<< orphan*/ ,int) ; 
 int pt_insn_decode (struct pt_insn*,struct pt_insn_ext*,struct pt_image*,struct pt_asid const*) ; 
 int pt_insn_next_ip (scalar_t__*,struct pt_insn*,struct pt_insn_ext*) ; 

int pt_insn_range_is_contiguous(uint64_t begin, uint64_t end,
				enum pt_exec_mode mode, struct pt_image *image,
				const struct pt_asid *asid, size_t steps)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;

	memset(&insn, 0, sizeof(insn));

	insn.mode = mode;
	insn.ip = begin;

	while (insn.ip != end) {
		int errcode;

		if (!steps--)
			return 0;

		errcode = pt_insn_decode(&insn, &iext, image, asid);
		if (errcode < 0)
			return errcode;

		errcode = pt_insn_next_ip(&insn.ip, &insn, &iext);
		if (errcode < 0)
			return errcode;
	}

	return 1;
}
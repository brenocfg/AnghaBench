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
typedef  scalar_t__ uint8_t ;
struct pt_mapped_section {int dummy; } ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {scalar_t__ size; int /*<<< orphan*/  ip; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int pt_ild_decode (struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_msec_read (struct pt_mapped_section const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_decode_in_section(struct pt_insn *insn,
				    struct pt_insn_ext *iext,
				    const struct pt_mapped_section *msec)
{
	int status;

	if (!insn || !iext)
		return -pte_internal;

	/* We know that @ip is contained in @section.
	 *
	 * Note that we need to translate @ip into a section offset.
	 */
	status = pt_msec_read(msec, insn->raw, sizeof(insn->raw), insn->ip);
	if (status < 0)
		return status;

	/* We initialize @insn->size to the maximal possible size.  It will be
	 * set to the actual size during instruction decode.
	 */
	insn->size = (uint8_t) status;

	return pt_ild_decode(insn, iext);
}
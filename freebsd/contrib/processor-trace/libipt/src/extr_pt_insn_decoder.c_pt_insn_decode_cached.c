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
struct pt_insn_decoder {int /*<<< orphan*/  asid; int /*<<< orphan*/  image; } ;
struct pt_insn {scalar_t__ size; int /*<<< orphan*/  ip; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int pt_ild_decode (struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_decode (struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pt_msec_read (struct pt_mapped_section const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pte_bad_insn ; 
 int pte_internal ; 
 int pte_nomap ; 

__attribute__((used)) static int pt_insn_decode_cached(struct pt_insn_decoder *decoder,
				 const struct pt_mapped_section *msec,
				 struct pt_insn *insn, struct pt_insn_ext *iext)
{
	int status;

	if (!decoder || !insn || !iext)
		return -pte_internal;

	/* Try reading the memory containing @insn from the cached section.  If
	 * that fails, if we don't have a cached section, or if decode fails
	 * later on, fall back to decoding @insn from @decoder->image.
	 *
	 * The latter will also handle truncated instructions that cross section
	 * boundaries.
	 */

	if (!msec)
		return pt_insn_decode(insn, iext, decoder->image,
				      &decoder->asid);

	status = pt_msec_read(msec, insn->raw, sizeof(insn->raw), insn->ip);
	if (status < 0) {
		if (status != -pte_nomap)
			return status;

		return pt_insn_decode(insn, iext, decoder->image,
				      &decoder->asid);
	}

	/* We initialize @insn->size to the maximal possible size.  It will be
	 * set to the actual size during instruction decode.
	 */
	insn->size = (uint8_t) status;

	status = pt_ild_decode(insn, iext);
	if (status < 0) {
		if (status != -pte_bad_insn)
			return status;

		return pt_insn_decode(insn, iext, decoder->image,
				      &decoder->asid);
	}

	return status;
}
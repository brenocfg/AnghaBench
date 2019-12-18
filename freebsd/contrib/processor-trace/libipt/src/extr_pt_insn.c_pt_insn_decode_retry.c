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
typedef  int uint8_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int size; int truncated; scalar_t__ ip; int /*<<< orphan*/ * raw; } ;
struct pt_image {int dummy; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_ild_decode (struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_image_read (struct pt_image*,int*,int /*<<< orphan*/ *,int,struct pt_asid const*,scalar_t__) ; 
 int pte_bad_insn ; 
 int pte_internal ; 
 int pte_nomap ; 

__attribute__((used)) static int pt_insn_decode_retry(struct pt_insn *insn, struct pt_insn_ext *iext,
				struct pt_image *image,
				const struct pt_asid *asid)
{
	int size, errcode, isid;
	uint8_t isize, remaining;

	if (!insn)
		return -pte_internal;

	isize = insn->size;
	remaining = sizeof(insn->raw) - isize;

	/* We failed for real if we already read the maximum number of bytes for
	 * an instruction.
	 */
	if (!remaining)
		return -pte_bad_insn;

	/* Read the remaining bytes from the image. */
	size = pt_image_read(image, &isid, &insn->raw[isize], remaining, asid,
			     insn->ip + isize);
	if (size <= 0) {
		/* We should have gotten an error if we were not able to read at
		 * least one byte.  Check this to guarantee termination.
		 */
		if (!size)
			return -pte_internal;

		/* Preserve the original error if there are no more bytes. */
		if (size == -pte_nomap)
			size = -pte_bad_insn;

		return size;
	}

	/* Add the newly read bytes to the instruction's size. */
	insn->size += (uint8_t) size;

	/* Store the new size to avoid infinite recursion in case instruction
	 * decode fails after length decode, which would set @insn->size to the
	 * actual length.
	 */
	size = insn->size;

	/* Try to decode the instruction again.
	 *
	 * If we fail again, we recursively retry again until we either fail to
	 * read more bytes or reach the maximum number of bytes for an
	 * instruction.
	 */
	errcode = pt_ild_decode(insn, iext);
	if (errcode < 0) {
		if (errcode != -pte_bad_insn)
			return errcode;

		/* If instruction length decode already determined the size,
		 * there's no point in reading more bytes.
		 */
		if (insn->size != (uint8_t) size)
			return errcode;

		return pt_insn_decode_retry(insn, iext, image, asid);
	}

	/* We succeeded this time, so the instruction crosses image section
	 * boundaries.
	 *
	 * This poses the question which isid to use for the instruction.
	 *
	 * To reconstruct exactly this instruction at a later time, we'd need to
	 * store all isids involved together with the number of bytes read for
	 * each isid.  Since @insn already provides the exact bytes for this
	 * instruction, we assume that the isid will be used solely for source
	 * correlation.  In this case, it should refer to the first byte of the
	 * instruction - as it already does.
	 */
	insn->truncated = 1;

	return errcode;
}
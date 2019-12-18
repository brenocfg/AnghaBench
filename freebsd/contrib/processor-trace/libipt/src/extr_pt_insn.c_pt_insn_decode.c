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
typedef  int /*<<< orphan*/  uint8_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int /*<<< orphan*/  size; int /*<<< orphan*/  ip; int /*<<< orphan*/  raw; int /*<<< orphan*/  isid; } ;
struct pt_image {int dummy; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_ild_decode (struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_image_read (struct pt_image*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct pt_asid const*,int /*<<< orphan*/ ) ; 
 int pt_insn_decode_retry (struct pt_insn*,struct pt_insn_ext*,struct pt_image*,struct pt_asid const*) ; 
 int pte_bad_insn ; 
 int pte_internal ; 

int pt_insn_decode(struct pt_insn *insn, struct pt_insn_ext *iext,
		   struct pt_image *image, const struct pt_asid *asid)
{
	int size, errcode;

	if (!insn)
		return -pte_internal;

	/* Read the memory at the current IP in the current address space. */
	size = pt_image_read(image, &insn->isid, insn->raw, sizeof(insn->raw),
			     asid, insn->ip);
	if (size < 0)
		return size;

	/* We initialize @insn->size to the maximal possible size.  It will be
	 * set to the actual size during instruction decode.
	 */
	insn->size = (uint8_t) size;

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

	return errcode;
}
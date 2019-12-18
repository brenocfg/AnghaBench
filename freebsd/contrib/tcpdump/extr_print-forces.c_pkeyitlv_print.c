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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
struct forces_tlv {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
typedef  struct forces_tlv u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (struct forces_tlv const*) ; 
 int /*<<< orphan*/  ForCES_TLV_err ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct forces_tlv const) ; 
 scalar_t__ TLV_DATA (struct forces_tlv const*) ; 
 int fdatatlv_print (int /*<<< orphan*/ *,struct forces_tlv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* indent_pr (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tlv_valid (struct forces_tlv const*,scalar_t__) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
pkeyitlv_print(netdissect_options *ndo,
               register const u_char * pptr, register u_int len,
               uint16_t op_msk, int indent)
{
	const struct forces_tlv *tlv = (const struct forces_tlv *)pptr;
	register const u_char *tdp = (const u_char *) TLV_DATA(tlv);
	register const u_char *dp = tdp + 4;
	const struct forces_tlv *kdtlv = (const struct forces_tlv *)dp;
	uint32_t id;
	char *ib = indent_pr(indent, 0);
	uint16_t type, tll;
	u_int invtlv;

	ND_TCHECK(*tdp);
	id = EXTRACT_32BITS(tdp);
	ND_PRINT((ndo, "%sKeyinfo: Key 0x%x\n", ib, id));
	ND_TCHECK(*kdtlv);
	type = EXTRACT_16BITS(&kdtlv->type);
	invtlv = tlv_valid(kdtlv, len);

	if (invtlv) {
		ND_PRINT((ndo, "%s TLV type 0x%x len %d\n",
		       tok2str(ForCES_TLV_err, NULL, invtlv), type,
		       EXTRACT_16BITS(&kdtlv->length)));
		return -1;
	}
	/*
	 * At this point, tlv_valid() has ensured that the TLV
	 * length is large enough but not too large (it doesn't
	 * go past the end of the containing TLV).
	 */
	tll = EXTRACT_16BITS(&kdtlv->length);
	dp = (const u_char *) TLV_DATA(kdtlv);
	return fdatatlv_print(ndo, dp, tll, op_msk, indent);

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  void* u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct forces_tlv {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 void* EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ForCES_TLV ; 
 int /*<<< orphan*/  ForCES_TLV_err ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct forces_tlv const) ; 
 scalar_t__ TLV_DATA (struct forces_tlv const*) ; 
 void* TLV_HDRL ; 
 char* indent_pr (int,int /*<<< orphan*/ ) ; 
 int pdata_print (TYPE_1__*,int /*<<< orphan*/  const*,int,void*,int) ; 
 void* tlv_valid (struct forces_tlv const*,void*) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  ttlv_valid (void*) ; 

__attribute__((used)) static int
genoptlv_print(netdissect_options *ndo,
               register const u_char * pptr, register u_int len,
               uint16_t op_msk, int indent)
{
	const struct forces_tlv *pdtlv = (const struct forces_tlv *)pptr;
	uint16_t type;
	int tll;
	u_int invtlv;
	char *ib = indent_pr(indent, 0);

	ND_TCHECK(*pdtlv);
	type = EXTRACT_16BITS(&pdtlv->type);
	tll = EXTRACT_16BITS(&pdtlv->length) - TLV_HDRL;
	invtlv = tlv_valid(pdtlv, len);
	ND_PRINT((ndo, "genoptlvprint - %s TLV type 0x%x len %d\n",
	       tok2str(ForCES_TLV, NULL, type), type, EXTRACT_16BITS(&pdtlv->length)));
	if (!invtlv) {
		/*
		 * At this point, tlv_valid() has ensured that the TLV
		 * length is large enough but not too large (it doesn't
		 * go past the end of the containing TLV).
		 */
		register const u_char *dp = (const u_char *) TLV_DATA(pdtlv);
		if (!ttlv_valid(type)) {
			ND_PRINT((ndo, "%s TLV type 0x%x len %d\n",
			       tok2str(ForCES_TLV_err, NULL, invtlv), type,
			       EXTRACT_16BITS(&pdtlv->length)));
			return -1;
		}
		if (ndo->ndo_vflag >= 3)
			ND_PRINT((ndo, "%s%s, length %d (data length %d Bytes)",
			       ib, tok2str(ForCES_TLV, NULL, type),
			       EXTRACT_16BITS(&pdtlv->length), tll));

		return pdata_print(ndo, dp, tll, op_msk, indent + 1);
	} else {
		ND_PRINT((ndo, "\t\t\tInvalid ForCES TLV type=%x", type));
		return -1;
	}

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}
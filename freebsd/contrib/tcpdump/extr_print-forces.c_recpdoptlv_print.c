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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct forces_tlv {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ForCES_TLV ; 
 struct forces_tlv* GO_NXT_TLV (struct forces_tlv const*,scalar_t__) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct forces_tlv const) ; 
 scalar_t__ TLV_DATA (struct forces_tlv const*) ; 
 scalar_t__ TLV_HDRL ; 
 char* indent_pr (int,int /*<<< orphan*/ ) ; 
 int pdata_print (TYPE_1__*,int /*<<< orphan*/  const*,int,scalar_t__,int) ; 
 scalar_t__ tlv_valid (struct forces_tlv const*,scalar_t__) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
recpdoptlv_print(netdissect_options *ndo,
                 register const u_char * pptr, register u_int len,
                 uint16_t op_msk, int indent)
{
	const struct forces_tlv *pdtlv = (const struct forces_tlv *)pptr;
	int tll;
	u_int invtlv;
	uint16_t type;
	register const u_char *dp;
	char *ib;

	while (len != 0) {
		ND_TCHECK(*pdtlv);
		invtlv = tlv_valid(pdtlv, len);
		if (invtlv) {
			break;
		}

		/*
		 * At this point, tlv_valid() has ensured that the TLV
		 * length is large enough but not too large (it doesn't
		 * go past the end of the containing TLV).
		 */
		ib = indent_pr(indent, 0);
		type = EXTRACT_16BITS(&pdtlv->type);
		dp = (const u_char *) TLV_DATA(pdtlv);
		tll = EXTRACT_16BITS(&pdtlv->length) - TLV_HDRL;

		if (ndo->ndo_vflag >= 3)
			ND_PRINT((ndo, "%s%s, length %d (data encapsulated %d Bytes)",
			          ib, tok2str(ForCES_TLV, NULL, type),
			          EXTRACT_16BITS(&pdtlv->length),
			          EXTRACT_16BITS(&pdtlv->length) - TLV_HDRL));

		if (pdata_print(ndo, dp, tll, op_msk, indent + 1) == -1)
			return -1;
		pdtlv = GO_NXT_TLV(pdtlv, len);
	}

	if (len) {
		ND_PRINT((ndo,
		          "\n\t\tMessy PATHDATA TLV header, type (0x%x)\n\t\texcess of %d Bytes ",
		          EXTRACT_16BITS(&pdtlv->type), len - EXTRACT_16BITS(&pdtlv->length)));
		return -1;
	}

	return 0;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pdata_ops {scalar_t__ v; int (* print ) (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,int) ;int /*<<< orphan*/  op_msk; int /*<<< orphan*/  s; } ;
struct forces_tlv {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ B_APPND ; 
 scalar_t__ B_KEYIN ; 
 scalar_t__ B_TRNG ; 
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 scalar_t__ F_ALN_LEN (int) ; 
 scalar_t__ F_TLV_PDAT ; 
 int /*<<< orphan*/  ForCES_TLV_err ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct forces_tlv const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 scalar_t__ PTH_DESC_SIZE ; 
 scalar_t__ TLV_HDRL ; 
 int /*<<< orphan*/  chk_op_type (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct pdata_ops* get_forces_pd (scalar_t__) ; 
 int /*<<< orphan*/  hex_print_with_offset (TYPE_1__*,char*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* indent_pr (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pd_valid (scalar_t__) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ tlv_valid (struct forces_tlv const*,scalar_t__) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
pdatacnt_print(netdissect_options *ndo,
               register const u_char * pptr, register u_int len,
               uint16_t IDcnt, uint16_t op_msk, int indent)
{
	u_int i;
	uint32_t id;
	char *ib = indent_pr(indent, 0);

	if ((op_msk & B_APPND) && ndo->ndo_vflag >= 3) {
		ND_PRINT((ndo, "%sTABLE APPEND\n", ib));
	}
	for (i = 0; i < IDcnt; i++) {
		ND_TCHECK2(*pptr, 4);
		if (len < 4)
			goto trunc;
		id = EXTRACT_32BITS(pptr);
		if (ndo->ndo_vflag >= 3)
			ND_PRINT((ndo, "%sID#%02u: %d\n", ib, i + 1, id));
		len -= 4;
		pptr += 4;
	}

	if ((op_msk & B_TRNG) || (op_msk & B_KEYIN)) {
		if (op_msk & B_TRNG) {
			uint32_t starti, endi;

			if (len < PTH_DESC_SIZE) {
				ND_PRINT((ndo, "pathlength %d with key/range too short %d\n",
				       len, PTH_DESC_SIZE));
				return -1;
			}

			pptr += sizeof(struct forces_tlv);
			len -= sizeof(struct forces_tlv);

			starti = EXTRACT_32BITS(pptr);
			pptr += 4;
			len -= 4;

			endi = EXTRACT_32BITS(pptr);
			pptr += 4;
			len -= 4;

			if (ndo->ndo_vflag >= 3)
				ND_PRINT((ndo, "%sTable range: [%d,%d]\n", ib, starti, endi));
		}

		if (op_msk & B_KEYIN) {
			const struct forces_tlv *keytlv;
			uint16_t tll;

			if (len < PTH_DESC_SIZE) {
				ND_PRINT((ndo, "pathlength %d with key/range too short %d\n",
				       len, PTH_DESC_SIZE));
				return -1;
			}

			/* skip keyid */
			pptr += 4;
			len -= 4;
			keytlv = (const struct forces_tlv *)pptr;
			/* skip header */
			pptr += sizeof(struct forces_tlv);
			len -= sizeof(struct forces_tlv);
			/* skip key content */
			tll = EXTRACT_16BITS(&keytlv->length);
			if (tll < TLV_HDRL) {
				ND_PRINT((ndo, "key content length %u < %u\n",
					tll, TLV_HDRL));
				return -1;
			}
			tll -= TLV_HDRL;
			if (len < tll) {
				ND_PRINT((ndo, "key content too short\n"));
				return -1;
			}
			pptr += tll;
			len -= tll;
		}

	}

	if (len) {
		const struct forces_tlv *pdtlv = (const struct forces_tlv *)pptr;
		uint16_t type;
		uint16_t tll;
		int pad = 0;
		u_int aln;
		u_int invtlv;

		ND_TCHECK(*pdtlv);
		type = EXTRACT_16BITS(&pdtlv->type);
		invtlv = tlv_valid(pdtlv, len);
		if (invtlv) {
			ND_PRINT((ndo, "%s Outstanding bytes %d for TLV type 0x%x TLV len %d\n",
			          tok2str(ForCES_TLV_err, NULL, invtlv), len, type,
			          EXTRACT_16BITS(&pdtlv->length)));
			goto pd_err;
		}
		/*
		 * At this point, tlv_valid() has ensured that the TLV
		 * length is large enough but not too large (it doesn't
		 * go past the end of the containing TLV).
		 */
		tll = EXTRACT_16BITS(&pdtlv->length) - TLV_HDRL;
		aln = F_ALN_LEN(EXTRACT_16BITS(&pdtlv->length));
		if (aln > EXTRACT_16BITS(&pdtlv->length)) {
			if (aln > len) {
				ND_PRINT((ndo,
				          "Invalid padded pathdata TLV type 0x%x len %d missing %d pad bytes\n",
				          type, EXTRACT_16BITS(&pdtlv->length), aln - len));
			} else {
				pad = aln - EXTRACT_16BITS(&pdtlv->length);
			}
		}
		if (pd_valid(type)) {
			const struct pdata_ops *ops = get_forces_pd(type);

			if (ndo->ndo_vflag >= 3 && ops->v != F_TLV_PDAT) {
				if (pad)
					ND_PRINT((ndo, "%s  %s (Length %d DataLen %d pad %d Bytes)\n",
					          ib, ops->s, EXTRACT_16BITS(&pdtlv->length), tll, pad));
				else
					ND_PRINT((ndo, "%s  %s (Length %d DataLen %d Bytes)\n",
					          ib, ops->s, EXTRACT_16BITS(&pdtlv->length), tll));
			}

			chk_op_type(ndo, type, op_msk, ops->op_msk);

			if (ops->print(ndo, (const u_char *)pdtlv,
					tll + pad + TLV_HDRL, op_msk,
					indent + 2) == -1)
				return -1;
			len -= (TLV_HDRL + pad + tll);
		} else {
			ND_PRINT((ndo, "Invalid path data content type 0x%x len %d\n",
			       type, EXTRACT_16BITS(&pdtlv->length)));
pd_err:
			if (EXTRACT_16BITS(&pdtlv->length)) {
                                hex_print_with_offset(ndo, "Bad Data val\n\t  [",
						      pptr, len, 0);
				ND_PRINT((ndo, "]\n"));

				return -1;
			}
		}
	}
	return len;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}
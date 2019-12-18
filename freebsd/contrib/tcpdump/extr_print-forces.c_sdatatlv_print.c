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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct forces_tlv {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ F_TLV_SPAD ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct forces_tlv const) ; 
 scalar_t__ TLV_DATA (struct forces_tlv const*) ; 
 scalar_t__ TLV_HDRL ; 
 int sdatailv_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
sdatatlv_print(netdissect_options *ndo,
               register const u_char * pptr, register u_int len,
               uint16_t op_msk, int indent)
{
	const struct forces_tlv *tlv = (const struct forces_tlv *)pptr;
	u_int rlen;
	register const u_char *tdp = (const u_char *) TLV_DATA(tlv);
	uint16_t type;

	/*
	 * pdatacnt_print() has ensured that len (the TLV length)
	 * >= TLV_HDRL.
	 */
	rlen = len - TLV_HDRL;
	ND_TCHECK(*tlv);
	type = EXTRACT_16BITS(&tlv->type);
	if (type != F_TLV_SPAD) {
		ND_PRINT((ndo, "Error: expecting SPARSEDATA!\n"));
		return -1;
	}

	return sdatailv_print(ndo, tdp, rlen, op_msk, indent);

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}
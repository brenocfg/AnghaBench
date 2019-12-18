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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int FALSE ; 
 int L2TP_FLAG_LENGTH ; 
 int L2TP_FLAG_OFFSET ; 
 int L2TP_FLAG_PRIORITY ; 
 int L2TP_FLAG_SEQUENCE ; 
 int L2TP_FLAG_TYPE ; 
 int L2TP_VERSION_L2F ; 
 int L2TP_VERSION_L2TP ; 
 int L2TP_VERSION_MASK ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  l2tp_avp_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ppp_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
l2tp_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const u_char *ptr = dat;
	u_int cnt = 0;			/* total octets consumed */
	uint16_t pad;
	int flag_t, flag_l, flag_s, flag_o;
	uint16_t l2tp_len;

	flag_t = flag_l = flag_s = flag_o = FALSE;

	ND_TCHECK2(*ptr, 2);	/* Flags & Version */
	if ((EXTRACT_16BITS(ptr) & L2TP_VERSION_MASK) == L2TP_VERSION_L2TP) {
		ND_PRINT((ndo, " l2tp:"));
	} else if ((EXTRACT_16BITS(ptr) & L2TP_VERSION_MASK) == L2TP_VERSION_L2F) {
		ND_PRINT((ndo, " l2f:"));
		return;		/* nothing to do */
	} else {
		ND_PRINT((ndo, " Unknown Version, neither L2F(1) nor L2TP(2)"));
		return;		/* nothing we can do */
	}

	ND_PRINT((ndo, "["));
	if (EXTRACT_16BITS(ptr) & L2TP_FLAG_TYPE) {
		flag_t = TRUE;
		ND_PRINT((ndo, "T"));
	}
	if (EXTRACT_16BITS(ptr) & L2TP_FLAG_LENGTH) {
		flag_l = TRUE;
		ND_PRINT((ndo, "L"));
	}
	if (EXTRACT_16BITS(ptr) & L2TP_FLAG_SEQUENCE) {
		flag_s = TRUE;
		ND_PRINT((ndo, "S"));
	}
	if (EXTRACT_16BITS(ptr) & L2TP_FLAG_OFFSET) {
		flag_o = TRUE;
		ND_PRINT((ndo, "O"));
	}
	if (EXTRACT_16BITS(ptr) & L2TP_FLAG_PRIORITY)
		ND_PRINT((ndo, "P"));
	ND_PRINT((ndo, "]"));

	ptr += 2;
	cnt += 2;

	if (flag_l) {
		ND_TCHECK2(*ptr, 2);	/* Length */
		l2tp_len = EXTRACT_16BITS(ptr);
		ptr += 2;
		cnt += 2;
	} else {
		l2tp_len = 0;
	}

	ND_TCHECK2(*ptr, 2);		/* Tunnel ID */
	ND_PRINT((ndo, "(%u/", EXTRACT_16BITS(ptr)));
	ptr += 2;
	cnt += 2;
	ND_TCHECK2(*ptr, 2);		/* Session ID */
	ND_PRINT((ndo, "%u)",  EXTRACT_16BITS(ptr)));
	ptr += 2;
	cnt += 2;

	if (flag_s) {
		ND_TCHECK2(*ptr, 2);	/* Ns */
		ND_PRINT((ndo, "Ns=%u,", EXTRACT_16BITS(ptr)));
		ptr += 2;
		cnt += 2;
		ND_TCHECK2(*ptr, 2);	/* Nr */
		ND_PRINT((ndo, "Nr=%u",  EXTRACT_16BITS(ptr)));
		ptr += 2;
		cnt += 2;
	}

	if (flag_o) {
		ND_TCHECK2(*ptr, 2);	/* Offset Size */
		pad =  EXTRACT_16BITS(ptr);
		ptr += (2 + pad);
		cnt += (2 + pad);
	}

	if (flag_l) {
		if (length < l2tp_len) {
			ND_PRINT((ndo, " Length %u larger than packet", l2tp_len));
			return;
		}
		length = l2tp_len;
	}
	if (length < cnt) {
		ND_PRINT((ndo, " Length %u smaller than header length", length));
		return;
	}
	if (flag_t) {
		if (!flag_l) {
			ND_PRINT((ndo, " No length"));
			return;
		}
		if (length - cnt == 0) {
			ND_PRINT((ndo, " ZLB"));
		} else {
			l2tp_avp_print(ndo, ptr, length - cnt);
		}
	} else {
		ND_PRINT((ndo, " {"));
		ppp_print(ndo, ptr, length - cnt);
		ND_PRINT((ndo, "}"));
	}

	return;

 trunc:
	ND_PRINT((ndo, "%s", tstr));
}
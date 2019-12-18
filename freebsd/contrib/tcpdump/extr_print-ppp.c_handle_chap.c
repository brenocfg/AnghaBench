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
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  CHAP_CHAL 131 
#define  CHAP_FAIL 130 
#define  CHAP_RESP 129 
#define  CHAP_SUCC 128 
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  chapcode_values ; 
 int /*<<< orphan*/  safeputchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
handle_chap(netdissect_options *ndo,
            const u_char *p, int length)
{
	u_int code, len;
	int val_size, name_size, msg_size;
	const u_char *p0;
	int i;

	p0 = p;
	if (length < 1) {
		ND_PRINT((ndo, "[|chap]"));
		return;
	} else if (length < 4) {
		ND_TCHECK(*p);
		ND_PRINT((ndo, "[|chap 0x%02x]", *p));
		return;
	}

	ND_TCHECK(*p);
	code = *p;
	ND_PRINT((ndo, "CHAP, %s (0x%02x)",
               tok2str(chapcode_values,"unknown",code),
               code));
	p++;

	ND_TCHECK(*p);
	ND_PRINT((ndo, ", id %u", *p));		/* ID */
	p++;

	ND_TCHECK2(*p, 2);
	len = EXTRACT_16BITS(p);
	p += 2;

	/*
	 * Note that this is a generic CHAP decoding routine. Since we
	 * don't know which flavor of CHAP (i.e. CHAP-MD5, MS-CHAPv1,
	 * MS-CHAPv2) is used at this point, we can't decode packet
	 * specifically to each algorithms. Instead, we simply decode
	 * the GCD (Gratest Common Denominator) for all algorithms.
	 */
	switch (code) {
	case CHAP_CHAL:
	case CHAP_RESP:
		if (length - (p - p0) < 1)
			return;
		ND_TCHECK(*p);
		val_size = *p;		/* value size */
		p++;
		if (length - (p - p0) < val_size)
			return;
		ND_PRINT((ndo, ", Value "));
		for (i = 0; i < val_size; i++) {
			ND_TCHECK(*p);
			ND_PRINT((ndo, "%02x", *p++));
		}
		name_size = len - (p - p0);
		ND_PRINT((ndo, ", Name "));
		for (i = 0; i < name_size; i++) {
			ND_TCHECK(*p);
			safeputchar(ndo, *p++);
		}
		break;
	case CHAP_SUCC:
	case CHAP_FAIL:
		msg_size = len - (p - p0);
		ND_PRINT((ndo, ", Msg "));
		for (i = 0; i< msg_size; i++) {
			ND_TCHECK(*p);
			safeputchar(ndo, *p++);
		}
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, "[|chap]"));
}
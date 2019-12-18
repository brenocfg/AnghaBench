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
typedef  int u_short ;
typedef  int u_char ;
struct krb {int type; } ;
struct TYPE_5__ {int* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  AUTH_MSG_APPL_REQUEST 131 
#define  AUTH_MSG_ERR_REPLY 130 
#define  AUTH_MSG_KDC_REPLY 129 
#define  AUTH_MSG_KDC_REQUEST 128 
 scalar_t__ IS_LENDIAN (struct krb const*) ; 
 int KTOHSP (struct krb const*,int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  PRINT ; 
 int /*<<< orphan*/  kerr2str ; 
 int* krb4_print_hdr (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  type2str ; 

__attribute__((used)) static void
krb4_print(netdissect_options *ndo,
           const u_char *cp)
{
	register const struct krb *kp;
	u_char type;
	u_short len;

#define PRINT		if ((cp = c_print(ndo, cp, ndo->ndo_snapend)) == NULL) goto trunc
/*  True if struct krb is little endian */
#define IS_LENDIAN(kp)	(((kp)->type & 0x01) != 0)
#define KTOHSP(kp, cp)	(IS_LENDIAN(kp) ? EXTRACT_LE_16BITS(cp) : EXTRACT_16BITS(cp))

	kp = (const struct krb *)cp;

	if ((&kp->type) >= ndo->ndo_snapend) {
		ND_PRINT((ndo, "%s", tstr));
		return;
	}

	type = kp->type & (0xFF << 1);

	ND_PRINT((ndo, " %s %s: ",
	    IS_LENDIAN(kp) ? "le" : "be", tok2str(type2str, NULL, type)));

	switch (type) {

	case AUTH_MSG_KDC_REQUEST:
		if ((cp = krb4_print_hdr(ndo, cp)) == NULL)
			return;
		cp += 4;	/* ctime */
		ND_TCHECK(*cp);
		ND_PRINT((ndo, " %dmin ", *cp++ * 5));
		PRINT;
		ND_PRINT((ndo, "."));
		PRINT;
		break;

	case AUTH_MSG_APPL_REQUEST:
		cp += 2;
		ND_TCHECK(*cp);
		ND_PRINT((ndo, "v%d ", *cp++));
		PRINT;
		ND_TCHECK(*cp);
		ND_PRINT((ndo, " (%d)", *cp++));
		ND_TCHECK(*cp);
		ND_PRINT((ndo, " (%d)", *cp));
		break;

	case AUTH_MSG_KDC_REPLY:
		if ((cp = krb4_print_hdr(ndo, cp)) == NULL)
			return;
		cp += 10;	/* timestamp + n + exp + kvno */
		ND_TCHECK2(*cp, sizeof(short));
		len = KTOHSP(kp, cp);
		ND_PRINT((ndo, " (%d)", len));
		break;

	case AUTH_MSG_ERR_REPLY:
		if ((cp = krb4_print_hdr(ndo, cp)) == NULL)
			return;
		cp += 4; 	  /* timestamp */
		ND_TCHECK2(*cp, sizeof(short));
		ND_PRINT((ndo, " %s ", tok2str(kerr2str, NULL, KTOHSP(kp, cp))));
		cp += 4;
		PRINT;
		break;

	default:
		ND_PRINT((ndo, "(unknown)"));
		break;
	}

	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  size_t u_int ;
typedef  scalar_t__ u_char ;
struct TYPE_14__ {scalar_t__ const* ndo_snapend; int /*<<< orphan*/  ndo_xflag; scalar_t__ ndo_eflag; int /*<<< orphan*/  ndo_suppress_default_print; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int ETHERTYPE_LEN ; 
 int EXTRACT_16BITS (scalar_t__ const*) ; 
 scalar_t__ const LLC_UI ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (scalar_t__ const) ; 
 int /*<<< orphan*/  ND_TTEST2 (scalar_t__ const,int) ; 
#define  NLPID_CLNP 136 
#define  NLPID_ESIS 135 
#define  NLPID_IP 134 
#define  NLPID_IP6 133 
#define  NLPID_ISIS 132 
#define  NLPID_MFR 131 
#define  NLPID_PPP 130 
#define  NLPID_Q933 129 
#define  NLPID_SNAP 128 
 scalar_t__ ethertype_print (TYPE_1__*,int,scalar_t__ const*,size_t,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fr_hdr_print (TYPE_1__*,size_t,size_t,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  frf15_print (TYPE_1__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  ip6_print (TYPE_1__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  isoclns_print (TYPE_1__*,scalar_t__ const*,size_t) ; 
 int parse_q922_addr (TYPE_1__*,scalar_t__ const*,size_t*,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ppp_print (TYPE_1__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  q933_print (TYPE_1__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  snap_print (TYPE_1__*,scalar_t__ const*,size_t,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u_int
fr_print(netdissect_options *ndo,
         register const u_char *p, u_int length)
{
	int ret;
	uint16_t extracted_ethertype;
	u_int dlci;
	u_int addr_len;
	uint16_t nlpid;
	u_int hdr_len;
	uint8_t flags[4];

	ret = parse_q922_addr(ndo, p, &dlci, &addr_len, flags, length);
	if (ret == -1)
		goto trunc;
	if (ret == 0) {
		ND_PRINT((ndo, "Q.922, invalid address"));
		return 0;
	}

	ND_TCHECK(p[addr_len]);
	if (length < addr_len + 1)
		goto trunc;

	if (p[addr_len] != LLC_UI && dlci != 0) {
                /*
                 * Let's figure out if we have Cisco-style encapsulation,
                 * with an Ethernet type (Cisco HDLC type?) following the
                 * address.
                 */
		if (!ND_TTEST2(p[addr_len], 2) || length < addr_len + 2) {
                        /* no Ethertype */
                        ND_PRINT((ndo, "UI %02x! ", p[addr_len]));
                } else {
                        extracted_ethertype = EXTRACT_16BITS(p+addr_len);

                        if (ndo->ndo_eflag)
                                fr_hdr_print(ndo, length, addr_len, dlci,
                                    flags, extracted_ethertype);

                        if (ethertype_print(ndo, extracted_ethertype,
                                            p+addr_len+ETHERTYPE_LEN,
                                            length-addr_len-ETHERTYPE_LEN,
                                            ndo->ndo_snapend-p-addr_len-ETHERTYPE_LEN,
                                            NULL, NULL) == 0)
                                /* ether_type not known, probably it wasn't one */
                                ND_PRINT((ndo, "UI %02x! ", p[addr_len]));
                        else
                                return addr_len + 2;
                }
        }

	ND_TCHECK(p[addr_len+1]);
	if (length < addr_len + 2)
		goto trunc;

	if (p[addr_len + 1] == 0) {
		/*
		 * Assume a pad byte after the control (UI) byte.
		 * A pad byte should only be used with 3-byte Q.922.
		 */
		if (addr_len != 3)
			ND_PRINT((ndo, "Pad! "));
		hdr_len = addr_len + 1 /* UI */ + 1 /* pad */ + 1 /* NLPID */;
	} else {
		/*
		 * Not a pad byte.
		 * A pad byte should be used with 3-byte Q.922.
		 */
		if (addr_len == 3)
			ND_PRINT((ndo, "No pad! "));
		hdr_len = addr_len + 1 /* UI */ + 1 /* NLPID */;
	}

        ND_TCHECK(p[hdr_len - 1]);
	if (length < hdr_len)
		goto trunc;
	nlpid = p[hdr_len - 1];

	if (ndo->ndo_eflag)
		fr_hdr_print(ndo, length, addr_len, dlci, flags, nlpid);
	p += hdr_len;
	length -= hdr_len;

	switch (nlpid) {
	case NLPID_IP:
	        ip_print(ndo, p, length);
		break;

	case NLPID_IP6:
		ip6_print(ndo, p, length);
		break;

	case NLPID_CLNP:
	case NLPID_ESIS:
	case NLPID_ISIS:
		isoclns_print(ndo, p - 1, length + 1); /* OSI printers need the NLPID field */
		break;

	case NLPID_SNAP:
		if (snap_print(ndo, p, length, ndo->ndo_snapend - p, NULL, NULL, 0) == 0) {
			/* ether_type not known, print raw packet */
                        if (!ndo->ndo_eflag)
                            fr_hdr_print(ndo, length + hdr_len, hdr_len,
                                         dlci, flags, nlpid);
			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(p - hdr_len, length + hdr_len);
		}
		break;

        case NLPID_Q933:
		q933_print(ndo, p, length);
		break;

        case NLPID_MFR:
                frf15_print(ndo, p, length);
                break;

        case NLPID_PPP:
                ppp_print(ndo, p, length);
                break;

	default:
		if (!ndo->ndo_eflag)
                    fr_hdr_print(ndo, length + hdr_len, addr_len,
				     dlci, flags, nlpid);
		if (!ndo->ndo_xflag)
			ND_DEFAULTPRINT(p, length);
	}

	return hdr_len;

 trunc:
        ND_PRINT((ndo, "[|fr]"));
        return 0;

}
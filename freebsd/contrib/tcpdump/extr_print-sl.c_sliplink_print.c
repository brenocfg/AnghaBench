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
typedef  size_t u_int ;
typedef  int u_char ;
struct tcphdr {int dummy; } ;
struct ip {size_t ip_p; } ;
struct TYPE_5__ {scalar_t__ ndo_nflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int CHDR_LEN ; 
 size_t IP_HL (struct ip const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
#define  SLIPDIR_IN 131 
#define  SLIPDIR_OUT 130 
 size_t SLIP_HDRLEN ; 
 int SLX_CHDR ; 
 size_t SLX_DIR ; 
 size_t TH_OFF (struct tcphdr const*) ; 
 int const TYPE_COMPRESSED_TCP ; 
#define  TYPE_IP 129 
#define  TYPE_UNCOMPRESSED_TCP 128 
 int /*<<< orphan*/  compressed_sl_print (TYPE_1__*,int const*,struct ip const*,size_t,int) ; 
 size_t lastconn ; 
 size_t** lastlen ; 

__attribute__((used)) static void
sliplink_print(netdissect_options *ndo,
               register const u_char *p, register const struct ip *ip,
               register u_int length)
{
	int dir;
	u_int hlen;

	dir = p[SLX_DIR];
	switch (dir) {

	case SLIPDIR_IN:
		ND_PRINT((ndo, "I "));
		break;

	case SLIPDIR_OUT:
		ND_PRINT((ndo, "O "));
		break;

	default:
		ND_PRINT((ndo, "Invalid direction %d ", dir));
		dir = -1;
		break;
	}
	if (ndo->ndo_nflag) {
		/* XXX just dump the header */
		register int i;

		for (i = SLX_CHDR; i < SLX_CHDR + CHDR_LEN - 1; ++i)
			ND_PRINT((ndo, "%02x.", p[i]));
		ND_PRINT((ndo, "%02x: ", p[SLX_CHDR + CHDR_LEN - 1]));
		return;
	}
	switch (p[SLX_CHDR] & 0xf0) {

	case TYPE_IP:
		ND_PRINT((ndo, "ip %d: ", length + SLIP_HDRLEN));
		break;

	case TYPE_UNCOMPRESSED_TCP:
		/*
		 * The connection id is stored in the IP protocol field.
		 * Get it from the link layer since sl_uncompress_tcp()
		 * has restored the IP header copy to IPPROTO_TCP.
		 */
		lastconn = ((const struct ip *)&p[SLX_CHDR])->ip_p;
		ND_PRINT((ndo, "utcp %d: ", lastconn));
		if (dir == -1) {
			/* Direction is bogus, don't use it */
			return;
		}
		hlen = IP_HL(ip);
		hlen += TH_OFF((const struct tcphdr *)&((const int *)ip)[hlen]);
		lastlen[dir][lastconn] = length - (hlen << 2);
		break;

	default:
		if (dir == -1) {
			/* Direction is bogus, don't use it */
			return;
		}
		if (p[SLX_CHDR] & TYPE_COMPRESSED_TCP) {
			compressed_sl_print(ndo, &p[SLX_CHDR], ip,
			    length, dir);
			ND_PRINT((ndo, ": "));
		} else
			ND_PRINT((ndo, "slip-%d!: ", p[SLX_CHDR]));
	}
}
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
typedef  int /*<<< orphan*/  u_char ;
struct tcphdr {int dummy; } ;
struct ip {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int IP_HL (struct ip const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int NEW_A ; 
 int NEW_C ; 
 int NEW_I ; 
 int NEW_S ; 
 int NEW_U ; 
 int NEW_W ; 
 int SPECIALS_MASK ; 
#define  SPECIAL_D 129 
#define  SPECIAL_I 128 
 scalar_t__ TH_OFF (struct tcphdr const*) ; 
 size_t lastconn ; 
 int** lastlen ; 
 int /*<<< orphan*/ * print_sl_change (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * print_sl_winchange (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
compressed_sl_print(netdissect_options *ndo,
                    const u_char *chdr, const struct ip *ip,
                    u_int length, int dir)
{
	register const u_char *cp = chdr;
	register u_int flags, hlen;

	flags = *cp++;
	if (flags & NEW_C) {
		lastconn = *cp++;
		ND_PRINT((ndo, "ctcp %d", lastconn));
	} else
		ND_PRINT((ndo, "ctcp *"));

	/* skip tcp checksum */
	cp += 2;

	switch (flags & SPECIALS_MASK) {
	case SPECIAL_I:
		ND_PRINT((ndo, " *SA+%d", lastlen[dir][lastconn]));
		break;

	case SPECIAL_D:
		ND_PRINT((ndo, " *S+%d", lastlen[dir][lastconn]));
		break;

	default:
		if (flags & NEW_U)
			cp = print_sl_change(ndo, "U=", cp);
		if (flags & NEW_W)
			cp = print_sl_winchange(ndo, cp);
		if (flags & NEW_A)
			cp = print_sl_change(ndo, "A+", cp);
		if (flags & NEW_S)
			cp = print_sl_change(ndo, "S+", cp);
		break;
	}
	if (flags & NEW_I)
		cp = print_sl_change(ndo, "I+", cp);

	/*
	 * 'hlen' is the length of the uncompressed TCP/IP header (in words).
	 * 'cp - chdr' is the length of the compressed header.
	 * 'length - hlen' is the amount of data in the packet.
	 */
	hlen = IP_HL(ip);
	hlen += TH_OFF((const struct tcphdr *)&((const int32_t *)ip)[hlen]);
	lastlen[dir][lastconn] = length - (hlen << 2);
	ND_PRINT((ndo, " %d (%ld)", lastlen[dir][lastconn], (long)(cp - chdr)));
}
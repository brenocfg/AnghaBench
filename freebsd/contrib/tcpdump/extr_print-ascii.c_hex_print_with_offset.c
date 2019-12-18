#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ HEXDUMP_BYTES_PER_LINE ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 

void
hex_print_with_offset(netdissect_options *ndo,
                      const char *ident, const u_char *cp, u_int length,
		      u_int oset)
{
	u_int caplength;
	register u_int i, s;
	register int nshorts;

	caplength = (ndo->ndo_snapend >= cp) ? ndo->ndo_snapend - cp : 0;
	if (length > caplength)
		length = caplength;
	nshorts = (u_int) length / sizeof(u_short);
	i = 0;
	while (--nshorts >= 0) {
		if ((i++ % 8) == 0) {
			ND_PRINT((ndo,"%s0x%04x: ", ident, oset));
			oset += HEXDUMP_BYTES_PER_LINE;
		}
		s = *cp++;
		ND_PRINT((ndo," %02x%02x", s, *cp++));
	}
	if (length & 1) {
		if ((i % 8) == 0)
			ND_PRINT((ndo,"%s0x%04x: ", ident, oset));
		ND_PRINT((ndo," %02x", *cp));
	}
}
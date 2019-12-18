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
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
struct TYPE_7__ {scalar_t__ const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  EDNS0_ELT_BITLABEL 128 
 scalar_t__ EDNS0_MASK ; 
 scalar_t__ INDIR_MASK ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TTEST2 (scalar_t__ const,int) ; 
 int /*<<< orphan*/ * blabel_print (TYPE_1__*,scalar_t__ const*) ; 
 scalar_t__ fn_printn (TYPE_1__*,scalar_t__ const*,scalar_t__,scalar_t__ const*) ; 
 scalar_t__ labellen (TYPE_1__*,scalar_t__ const*) ; 

const u_char *
ns_nprint(netdissect_options *ndo,
          register const u_char *cp, register const u_char *bp)
{
	register u_int i, l;
	register const u_char *rp = NULL;
	register int compress = 0;
	int elt;
	u_int offset, max_offset;

	if ((l = labellen(ndo, cp)) == (u_int)-1)
		return(NULL);
	if (!ND_TTEST2(*cp, 1))
		return(NULL);
	max_offset = (u_int)(cp - bp);
	if (((i = *cp++) & INDIR_MASK) != INDIR_MASK) {
		compress = 0;
		rp = cp + l;
	}

	if (i != 0)
		while (i && cp < ndo->ndo_snapend) {
			if ((i & INDIR_MASK) == INDIR_MASK) {
				if (!compress) {
					rp = cp + 1;
					compress = 1;
				}
				if (!ND_TTEST2(*cp, 1))
					return(NULL);
				offset = (((i << 8) | *cp) & 0x3fff);
				/*
				 * This must move backwards in the packet.
				 * No RFC explicitly says that, but BIND's
				 * name decompression code requires it,
				 * as a way of preventing infinite loops
				 * and other bad behavior, and it's probably
				 * what was intended (compress by pointing
				 * to domain name suffixes already seen in
				 * the packet).
				 */
				if (offset >= max_offset) {
					ND_PRINT((ndo, "<BAD PTR>"));
					return(NULL);
				}
				max_offset = offset;
				cp = bp + offset;
				if ((l = labellen(ndo, cp)) == (u_int)-1)
					return(NULL);
				if (!ND_TTEST2(*cp, 1))
					return(NULL);
				i = *cp++;
				continue;
			}
			if ((i & INDIR_MASK) == EDNS0_MASK) {
				elt = (i & ~INDIR_MASK);
				switch(elt) {
				case EDNS0_ELT_BITLABEL:
					if (blabel_print(ndo, cp) == NULL)
						return (NULL);
					break;
				default:
					/* unknown ELT */
					ND_PRINT((ndo, "<ELT %d>", elt));
					return(NULL);
				}
			} else {
				if (fn_printn(ndo, cp, l, ndo->ndo_snapend))
					return(NULL);
			}

			cp += l;
			ND_PRINT((ndo, "."));
			if ((l = labellen(ndo, cp)) == (u_int)-1)
				return(NULL);
			if (!ND_TTEST2(*cp, 1))
				return(NULL);
			i = *cp++;
			if (!compress)
				rp += l + 1;
		}
	else
		ND_PRINT((ndo, "."));
	return (rp);
}
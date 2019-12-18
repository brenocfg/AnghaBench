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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EDNS0_ELT_BITLABEL ; 
 int EDNS0_MASK ; 
 int INDIR_MASK ; 
 int /*<<< orphan*/  ND_TTEST2 (int const,int) ; 

__attribute__((used)) static const u_char *
ns_nskip(netdissect_options *ndo,
         register const u_char *cp)
{
	register u_char i;

	if (!ND_TTEST2(*cp, 1))
		return (NULL);
	i = *cp++;
	while (i) {
		if ((i & INDIR_MASK) == INDIR_MASK)
			return (cp + 1);
		if ((i & INDIR_MASK) == EDNS0_MASK) {
			int bitlen, bytelen;

			if ((i & ~INDIR_MASK) != EDNS0_ELT_BITLABEL)
				return(NULL); /* unknown ELT */
			if (!ND_TTEST2(*cp, 1))
				return (NULL);
			if ((bitlen = *cp++) == 0)
				bitlen = 256;
			bytelen = (bitlen + 7) / 8;
			cp += bytelen;
		} else
			cp += i;
		if (!ND_TTEST2(*cp, 1))
			return (NULL);
		i = *cp++;
	}
	return (cp);
}
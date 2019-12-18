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

/* Variables and functions */
 int DNS_LABELTYPE_BITSTRING ; 
 int NS_CMPRSFLGS ; 
 int NS_TYPE_ELT ; 

__attribute__((used)) static int
labellen(const u_char *lp)
{
	int bitlen;
	u_char l = *lp;

	if ((l & NS_CMPRSFLGS) == NS_CMPRSFLGS) {
		/* should be avoided by the caller */
		return (-1);
	}

	if ((l & NS_CMPRSFLGS) == NS_TYPE_ELT) {
		if (l == DNS_LABELTYPE_BITSTRING) {
			if ((bitlen = *(lp + 1)) == 0)
				bitlen = 256;
			return ((bitlen + 7 ) / 8 + 1);
		}
		return (-1);	/*%< unknwon ELT */
	}
	return (l);
}
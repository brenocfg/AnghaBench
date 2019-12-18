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
typedef  char u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safeputchar (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static void
dnsname_print(netdissect_options *ndo, const u_char *cp, const u_char *ep)
{
	int i;

	/* DNS name decoding - no decompression */
	ND_PRINT((ndo,", \""));
	while (cp < ep) {
		i = *cp++;
		if (i) {
			if (i > ep - cp) {
				ND_PRINT((ndo,"???"));
				break;
			}
			while (i-- && cp < ep) {
				safeputchar(ndo, *cp);
				cp++;
			}
			if (cp + 1 < ep && *cp)
				ND_PRINT((ndo,"."));
		} else {
			if (cp == ep) {
				/* FQDN */
				ND_PRINT((ndo,"."));
			} else if (cp + 1 == ep && *cp == '\0') {
				/* truncated */
			} else {
				/* invalid */
				ND_PRINT((ndo,"???"));
			}
			break;
		}
	}
	ND_PRINT((ndo,"\""));
}
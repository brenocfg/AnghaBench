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
typedef  int uint8_t ;
struct ether_addr {int dummy; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  bcopy (struct ether_addr*,int*,int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 struct ether_addr* ether_aton (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 
 char* strsep (char**,char*) ; 
 size_t strspn (char*,char const*) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static void
get_mac_addr_mask(const char *p, uint8_t *addr, uint8_t *mask)
{
	int i;
	size_t l;
	char *ap, *ptr, *optr;
	struct ether_addr *mac;
	const char *macset = "0123456789abcdefABCDEF:";

	if (strcmp(p, "any") == 0) {
		for (i = 0; i < ETHER_ADDR_LEN; i++)
			addr[i] = mask[i] = 0;
		return;
	}

	optr = ptr = strdup(p);
	if ((ap = strsep(&ptr, "&/")) != NULL && *ap != 0) {
		l = strlen(ap);
		if (strspn(ap, macset) != l || (mac = ether_aton(ap)) == NULL)
			errx(EX_DATAERR, "Incorrect MAC address");
		bcopy(mac, addr, ETHER_ADDR_LEN);
	} else
		errx(EX_DATAERR, "Incorrect MAC address");

	if (ptr != NULL) { /* we have mask? */
		if (p[ptr - optr - 1] == '/') { /* mask len */
			long ml = strtol(ptr, &ap, 10);
			if (*ap != 0 || ml > ETHER_ADDR_LEN * 8 || ml < 0)
				errx(EX_DATAERR, "Incorrect mask length");
			for (i = 0; ml > 0 && i < ETHER_ADDR_LEN; ml -= 8, i++)
				mask[i] = (ml >= 8) ? 0xff: (~0) << (8 - ml);
		} else { /* mask */
			l = strlen(ptr);
			if (strspn(ptr, macset) != l ||
			    (mac = ether_aton(ptr)) == NULL)
				errx(EX_DATAERR, "Incorrect mask");
			bcopy(mac, mask, ETHER_ADDR_LEN);
		}
	} else { /* default mask: ff:ff:ff:ff:ff:ff */
		for (i = 0; i < ETHER_ADDR_LEN; i++)
			mask[i] = 0xff;
	}
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		addr[i] &= mask[i];

	free(optr);
}
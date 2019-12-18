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
typedef  int uint32_t ;

/* Variables and functions */
 int biospci_locator (int,int,int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
comc_parse_pcidev(const char *string)
{
#ifdef EFI
	/* We don't support PCI in EFI yet */
	return (0);
#else
	char *p, *p1;
	uint8_t bus, dev, func, bar;
	uint32_t locator;
	int pres;

	pres = strtol(string, &p, 0);
	if (p == string || *p != ':' || pres < 0 )
		return (0);
	bus = pres;
	p1 = ++p;

	pres = strtol(p1, &p, 0);
	if (p == string || *p != ':' || pres < 0 )
		return (0);
	dev = pres;
	p1 = ++p;

	pres = strtol(p1, &p, 0);
	if (p == string || (*p != ':' && *p != '\0') || pres < 0 )
		return (0);
	func = pres;

	if (*p == ':') {
		p1 = ++p;
		pres = strtol(p1, &p, 0);
		if (p == string || *p != '\0' || pres <= 0 )
			return (0);
		bar = pres;
	} else
		bar = 0x10;

	locator = (bar << 16) | biospci_locator(bus, dev, func);
	return (locator);
#endif
}
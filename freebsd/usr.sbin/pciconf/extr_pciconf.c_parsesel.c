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
struct pcisel {unsigned long pc_func; unsigned long pc_dev; unsigned long pc_bus; unsigned long pc_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ isdigit (char const) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static struct pcisel
parsesel(const char *str)
{
	const char *ep;
	char *eppos;
	struct pcisel sel;
	unsigned long selarr[4];
	int i;

	ep = strchr(str, '@');
	if (ep != NULL)
		ep++;
	else
		ep = str;

	if (strncmp(ep, "pci", 3) == 0) {
		ep += 3;
		i = 0;
		while (isdigit(*ep) && i < 4) {
			selarr[i++] = strtoul(ep, &eppos, 10);
			ep = eppos;
			if (*ep == ':')
				ep++;
		}
		if (i > 0 && *ep == '\0') {
			sel.pc_func = (i > 2) ? selarr[--i] : 0;
			sel.pc_dev = (i > 0) ? selarr[--i] : 0;
			sel.pc_bus = (i > 0) ? selarr[--i] : 0;
			sel.pc_domain = (i > 0) ? selarr[--i] : 0;
			return (sel);
		}
	}
	errx(1, "cannot parse selector %s", str);
}
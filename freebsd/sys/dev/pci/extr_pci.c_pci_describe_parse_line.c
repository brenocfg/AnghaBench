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

/* Variables and functions */
 char* pci_vendordata ; 
 int pci_vendordata_size ; 
 int sscanf (char*,char*,int*,char*) ; 

__attribute__((used)) static int
pci_describe_parse_line(char **ptr, int *vendor, int *device, char **desc)
{
	char	*cp = *ptr;
	int	left;

	*device = -1;
	*vendor = -1;
	**desc = '\0';
	for (;;) {
		left = pci_vendordata_size - (cp - pci_vendordata);
		if (left <= 0) {
			*ptr = cp;
			return(1);
		}

		/* vendor entry? */
		if (*cp != '\t' &&
		    sscanf(cp, "%x\t%80[^\n]", vendor, *desc) == 2)
			break;
		/* device entry? */
		if (*cp == '\t' &&
		    sscanf(cp, "%x\t%80[^\n]", device, *desc) == 2)
			break;

		/* skip to next line */
		while (*cp != '\n' && left > 0) {
			cp++;
			left--;
		}
		if (*cp == '\n') {
			cp++;
			left--;
		}
	}
	/* skip to next line */
	while (*cp != '\n' && left > 0) {
		cp++;
		left--;
	}
	if (*cp == '\n' && left > 0)
		cp++;
	*ptr = cp;
	return(0);
}
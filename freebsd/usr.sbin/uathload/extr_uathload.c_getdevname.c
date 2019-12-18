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
 char* basename (char*) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
getdevname(const char *udevname, char *msgdev, char *datadev)
{
	char *bn, *bnbuf, *dn, *dnbuf;

	dnbuf = strdup(udevname);
	if (dnbuf == NULL)
		return (-1);
	dn = dirname(dnbuf);
	bnbuf = strdup(udevname);
	if (bnbuf == NULL) {
		free(dnbuf);
		return (-1);
	}
	bn = basename(bnbuf);
	if (strncmp(bn, "ugen", 4) != 0) {
		free(dnbuf);
		free(bnbuf);
		return (-1);
	}
	bn += 4;

	/* NB: pipes are hardcoded */
	snprintf(msgdev, 256, "%s/usb/%s.1", dn, bn);
	snprintf(datadev, 256, "%s/usb/%s.2", dn, bn);
	free(dnbuf);
	free(bnbuf);
	return (0);
}
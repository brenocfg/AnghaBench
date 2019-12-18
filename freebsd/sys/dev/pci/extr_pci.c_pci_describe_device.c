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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_describe_parse_line (char**,int*,int*,char**) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 char* pci_vendordata ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
pci_describe_device(device_t dev)
{
	int	vendor, device;
	char	*desc, *vp, *dp, *line;

	desc = vp = dp = NULL;

	/*
	 * If we have no vendor data, we can't do anything.
	 */
	if (pci_vendordata == NULL)
		goto out;

	/*
	 * Scan the vendor data looking for this device
	 */
	line = pci_vendordata;
	if ((vp = malloc(80, M_DEVBUF, M_NOWAIT)) == NULL)
		goto out;
	for (;;) {
		if (pci_describe_parse_line(&line, &vendor, &device, &vp))
			goto out;
		if (vendor == pci_get_vendor(dev))
			break;
	}
	if ((dp = malloc(80, M_DEVBUF, M_NOWAIT)) == NULL)
		goto out;
	for (;;) {
		if (pci_describe_parse_line(&line, &vendor, &device, &dp)) {
			*dp = 0;
			break;
		}
		if (vendor != -1) {
			*dp = 0;
			break;
		}
		if (device == pci_get_device(dev))
			break;
	}
	if (dp[0] == '\0')
		snprintf(dp, 80, "0x%x", pci_get_device(dev));
	if ((desc = malloc(strlen(vp) + strlen(dp) + 3, M_DEVBUF, M_NOWAIT)) !=
	    NULL)
		sprintf(desc, "%s, %s", vp, dp);
out:
	if (vp != NULL)
		free(vp, M_DEVBUF);
	if (dp != NULL)
		free(dp, M_DEVBUF);
	return(desc);
}
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
typedef  long uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 long MFI_EVT_LOCALE_ALL ; 
 long MFI_EVT_LOCALE_BBU ; 
 long MFI_EVT_LOCALE_CLUSTER ; 
 long MFI_EVT_LOCALE_CONFIG ; 
 long MFI_EVT_LOCALE_CTRL ; 
 long MFI_EVT_LOCALE_ENCL ; 
 long MFI_EVT_LOCALE_LD ; 
 long MFI_EVT_LOCALE_PD ; 
 long MFI_EVT_LOCALE_SAS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_locale(char *arg, uint16_t *locale)
{
	char *cp;
	long val;

	if (strncasecmp(arg, "vol", 3) == 0 || strcasecmp(arg, "ld") == 0) {
		*locale = MFI_EVT_LOCALE_LD;
		return (0);
	}
	if (strncasecmp(arg, "drive", 5) == 0 || strcasecmp(arg, "pd") == 0) {
		*locale = MFI_EVT_LOCALE_PD;
		return (0);
	}
	if (strncasecmp(arg, "encl", 4) == 0) {
		*locale = MFI_EVT_LOCALE_ENCL;
		return (0);
	}
	if (strncasecmp(arg, "batt", 4) == 0 ||
	    strncasecmp(arg, "bbu", 3) == 0) {
		*locale = MFI_EVT_LOCALE_BBU;
		return (0);
	}
	if (strcasecmp(arg, "sas") == 0) {
		*locale = MFI_EVT_LOCALE_SAS;
		return (0);
	}
	if (strcasecmp(arg, "ctrl") == 0 || strncasecmp(arg, "cont", 4) == 0) {
		*locale = MFI_EVT_LOCALE_CTRL;
		return (0);
	}
	if (strcasecmp(arg, "config") == 0) {
		*locale = MFI_EVT_LOCALE_CONFIG;
		return (0);
	}
	if (strcasecmp(arg, "cluster") == 0) {
		*locale = MFI_EVT_LOCALE_CLUSTER;
		return (0);
	}
	if (strcasecmp(arg, "all") == 0) {
		*locale = MFI_EVT_LOCALE_ALL;
		return (0);
	}
	val = strtol(arg, &cp, 0);
	if (*cp != '\0' || val < 0 || val > 0xffff) {
		errno = EINVAL;
		return (-1);
	}
	*locale = val;
	return (0);
}
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
typedef  long int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 long MFI_EVT_CLASS_CRITICAL ; 
 long MFI_EVT_CLASS_DEAD ; 
 long MFI_EVT_CLASS_DEBUG ; 
 long MFI_EVT_CLASS_FATAL ; 
 long MFI_EVT_CLASS_INFO ; 
 long MFI_EVT_CLASS_PROGRESS ; 
 long MFI_EVT_CLASS_WARNING ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_class(char *arg, int8_t *class)
{
	char *cp;
	long val;

	if (strcasecmp(arg, "debug") == 0) {
		*class = MFI_EVT_CLASS_DEBUG;
		return (0);
	}
	if (strncasecmp(arg, "prog", 4) == 0) {
		*class = MFI_EVT_CLASS_PROGRESS;
		return (0);
	}
	if (strncasecmp(arg, "info", 4) == 0) {
		*class = MFI_EVT_CLASS_INFO;
		return (0);
	}
	if (strncasecmp(arg, "warn", 4) == 0) {
		*class = MFI_EVT_CLASS_WARNING;
		return (0);
	}
	if (strncasecmp(arg, "crit", 4) == 0) {
		*class = MFI_EVT_CLASS_CRITICAL;
		return (0);
	}
	if (strcasecmp(arg, "fatal") == 0) {
		*class = MFI_EVT_CLASS_FATAL;
		return (0);
	}
	if (strcasecmp(arg, "dead") == 0) {
		*class = MFI_EVT_CLASS_DEAD;
		return (0);
	}
	val = strtol(arg, &cp, 0);
	if (*cp != '\0' || val < -128 || val > 127) {
		errno = EINVAL;
		return (-1);
	}
	*class = val;
	return (0);
}
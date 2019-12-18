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
typedef  int /*<<< orphan*/  marker ;
typedef  int HostkeyMarker ;

/* Variables and functions */
 int /*<<< orphan*/  CA_MARKER ; 
 int MRK_CA ; 
 int MRK_ERROR ; 
 int MRK_NONE ; 
 int MRK_REVOKE ; 
 int /*<<< orphan*/  REVOKE_MARKER ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HostkeyMarker
check_markers(char **cpp)
{
	char marker[32], *sp, *cp = *cpp;
	int ret = MRK_NONE;

	while (*cp == '@') {
		/* Only one marker is allowed */
		if (ret != MRK_NONE)
			return MRK_ERROR;
		/* Markers are terminated by whitespace */
		if ((sp = strchr(cp, ' ')) == NULL &&
		    (sp = strchr(cp, '\t')) == NULL)
			return MRK_ERROR;
		/* Extract marker for comparison */
		if (sp <= cp + 1 || sp >= cp + sizeof(marker))
			return MRK_ERROR;
		memcpy(marker, cp, sp - cp);
		marker[sp - cp] = '\0';
		if (strcmp(marker, CA_MARKER) == 0)
			ret = MRK_CA;
		else if (strcmp(marker, REVOKE_MARKER) == 0)
			ret = MRK_REVOKE;
		else
			return MRK_ERROR;

		/* Skip past marker and any whitespace that follows it */
		cp = sp;
		for (; *cp == ' ' || *cp == '\t'; cp++)
			;
	}
	*cpp = cp;
	return ret;
}
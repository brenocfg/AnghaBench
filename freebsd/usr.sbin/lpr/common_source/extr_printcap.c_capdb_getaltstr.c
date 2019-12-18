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
 int PCAPERR_NOTFOUND ; 
 int PCAPERR_OSERR ; 
 int cgetstr (char*,char const*,char**) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
capdb_getaltstr(char *bp, const char *shrt, const char *lng, 
    const char *dflt, char **result)
{
	int status;

	status = cgetstr(bp, lng, result);
	if (status >= 0 || status == PCAPERR_OSERR)
		return status;
	status = cgetstr(bp, shrt, result);
	if (status >= 0 || status == PCAPERR_OSERR)
		return status;
	if (dflt) {
		*result = strdup(dflt);
		if (*result == NULL)
			return PCAPERR_OSERR;
		return strlen(*result);
	}
	return PCAPERR_NOTFOUND;
}
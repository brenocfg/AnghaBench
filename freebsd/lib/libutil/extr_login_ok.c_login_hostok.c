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
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  FNM_CASEFOLD ; 
 char** login_getcaplist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ login_str2inlist (char const**,char const*,char const*,int /*<<< orphan*/ ) ; 

int
login_hostok(login_cap_t *lc, const char *host, const char *ip,
	     const char *allowcap, const char *denycap)
{
    int	    rc = 1; /* Default is ok */

    if (lc != NULL &&
	((host != NULL && *host != '\0') || (ip != NULL && *ip != '\0'))) {
	const char **hl;

	hl = login_getcaplist(lc, allowcap, NULL);
	if (hl != NULL && !login_str2inlist(hl, host, ip, FNM_CASEFOLD))
	    rc = 0;	/* host or IP not in allow list */
	else {

	    hl = login_getcaplist(lc, denycap, NULL);
	    if (hl != NULL && login_str2inlist(hl, host, ip, FNM_CASEFOLD))
		rc = 0; /* host or IP in deny list */
	}
    }

    return rc;
}
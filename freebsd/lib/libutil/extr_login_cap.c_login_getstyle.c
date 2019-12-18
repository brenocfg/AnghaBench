#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  realauth ;
struct TYPE_4__ {char* lc_style; } ;
typedef  TYPE_1__ login_cap_t ;

/* Variables and functions */
#define  LOGIN_DEFSTYLE 128 
 char** login_getcaplist (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 void* strdup (char const*) ; 

const char *
login_getstyle(login_cap_t *lc, const char *style, const char *auth)
{
    int	    i;
    const char **authtypes = NULL;
    char    *auths= NULL;
    char    realauth[64];

    static const char *defauthtypes[] = { LOGIN_DEFSTYLE, NULL };

    if (auth != NULL && *auth != '\0') {
	if (snprintf(realauth, sizeof realauth, "auth-%s", auth) < (int)sizeof(realauth))
	    authtypes = login_getcaplist(lc, realauth, NULL);
    }

    if (authtypes == NULL)
	authtypes = login_getcaplist(lc, "auth", NULL);

    if (authtypes == NULL)
	authtypes = defauthtypes;

    /*
     * We have at least one authtype now; auths is a comma-separated
     * (or space-separated) list of authentication types.  We have to
     * convert from this to an array of char*'s; authtypes then gets this.
     */
    i = 0;
    if (style != NULL && *style != '\0') {
	while (authtypes[i] != NULL && strcmp(style, authtypes[i]) != 0)
	    i++;
    }

    lc->lc_style = NULL;
    if (authtypes[i] != NULL && (auths = strdup(authtypes[i])) != NULL)
	lc->lc_style = auths;

    if (lc->lc_style != NULL)
	lc->lc_style = strdup(lc->lc_style);

    return lc->lc_style;
}
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
struct ttyent {char* ty_group; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 struct ttyent* getttynam (char const*) ; 
 char** login_getcaplist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ login_str2inlist (char const**,char const*,char*,int /*<<< orphan*/ ) ; 

int
login_ttyok(login_cap_t *lc, const char *tty, const char *allowcap,
	    const char *denycap)
{
    int	    rc = 1;

    if (lc != NULL && tty != NULL && *tty != '\0') {
	struct ttyent	*te;
	char		*grp;
	const char	**ttl;

	te = getttynam(tty);  /* Need group name */
	grp = te ? te->ty_group : NULL;
	ttl = login_getcaplist(lc, allowcap, NULL);

	if (ttl != NULL && !login_str2inlist(ttl, tty, grp, 0))
	    rc = 0;	/* tty or ttygroup not in allow list */
	else {

	    ttl = login_getcaplist(lc, denycap, NULL);
	    if (ttl != NULL && login_str2inlist(ttl, tty, grp, 0))
		rc = 0; /* tty or ttygroup in deny list */
	}
    }

    return rc;
}
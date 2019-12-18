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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  ERR_SYSTEM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  const* short2str (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int strcmp (char*,char*) ; 
 int strcoll (char*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 char* strip (char*) ; 
 char* strsave (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

int
collate(const Char *a, const Char *b)
{
    int rv;
#ifdef SHORT_STRINGS
    /* This strips the quote bit as a side effect */
    char *sa = strsave(short2str(a));
    char *sb = strsave(short2str(b));
#else
    char *sa = strip(strsave(a));
    char *sb = strip(strsave(b));
#endif /* SHORT_STRINGS */

#if defined(NLS) && defined(HAVE_STRCOLL)
    errno = 0;	/* strcoll sets errno, another brain-damage */

    rv = strcoll(sa, sb);

    /*
     * We should be checking for errno != 0, but some systems
     * forget to reset errno to 0. So we only check for the 
     * only documented valid errno value for strcoll [EINVAL]
     */
    if (errno == EINVAL) {
	xfree(sa);
	xfree(sb);
	stderror(ERR_SYSTEM, "strcoll", strerror(errno));
    }
#else
    rv = strcmp(sa, sb);
#endif /* NLS && HAVE_STRCOLL */

    xfree(sa);
    xfree(sb);

    return rv;
}
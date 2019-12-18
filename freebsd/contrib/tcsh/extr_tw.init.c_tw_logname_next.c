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
struct passwd {int /*<<< orphan*/  pw_name; } ;
typedef  int Strbuf ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE (int*) ; 
 int /*<<< orphan*/  disabled_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fix_yp_bugs () ; 
 struct passwd* getpwent () ; 
 int /*<<< orphan*/  pintr_disabled ; 
 int /*<<< orphan*/  str2short (int /*<<< orphan*/ ) ; 

int
tw_logname_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    struct passwd *pw;

    /*
     * We don't want to get interrupted inside getpwent()
     * because the yellow pages code is not interruptible,
     * and if we call endpwent() immediatetely after
     * (in pintr()) we may be freeing an invalid pointer
     */
    USE(flags);
    USE(dir);
    pintr_disabled++;
#ifdef HAVE_GETPWENT
    pw = getpwent();
#else
    pw = NULL;
#endif
    disabled_cleanup(&pintr_disabled);

    if (pw == NULL) {
#ifdef YPBUGS
	fix_yp_bugs();
#endif
	return 0;
    }
    Strbuf_append(res, str2short(pw->pw_name));
    return 1;
}
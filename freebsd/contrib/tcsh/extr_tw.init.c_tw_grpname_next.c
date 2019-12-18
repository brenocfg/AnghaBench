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
struct group {int /*<<< orphan*/  gr_name; } ;
typedef  int Strbuf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  Strbuf_append (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE (int*) ; 
 int /*<<< orphan*/  disabled_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fix_yp_bugs () ; 
 struct group* getgrent () ; 
 int /*<<< orphan*/  handle_pending_signals () ; 
 int /*<<< orphan*/  pintr_disabled ; 
 int /*<<< orphan*/  str2short (int /*<<< orphan*/ ) ; 

int
tw_grpname_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    struct group *gr;

    /*
     * We don't want to get interrupted inside getgrent()
     * because the yellow pages code is not interruptible,
     * and if we call endgrent() immediatetely after
     * (in pintr()) we may be freeing an invalid pointer
     */
    USE(flags);
    USE(dir);
    pintr_disabled++;
#if !defined(_VMS_POSIX) && !defined(_OSD_POSIX) && !defined(WINNT_NATIVE) && !defined(__ANDROID__)
    errno = 0;
    while ((gr = getgrent()) == NULL && errno == EINTR) {
	handle_pending_signals();
	errno = 0;
    }
#else /* _VMS_POSIX || _OSD_POSIX || WINNT_NATIVE */
    gr = NULL;
#endif /* !_VMS_POSIX && !_OSD_POSIX && !WINNT_NATIVE */
    disabled_cleanup(&pintr_disabled);

    if (gr == NULL) {
#ifdef YPBUGS
	fix_yp_bugs();
#endif
	return 0;
    }
    Strbuf_append(res, str2short(gr->gr_name));
    return 1;
}
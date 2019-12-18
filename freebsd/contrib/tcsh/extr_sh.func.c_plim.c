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
struct rlimit {int rlim_max; int rlim_cur; } ;
struct limits {int limdiv; scalar_t__ limconst; int /*<<< orphan*/  limscale; int /*<<< orphan*/  limname; } ;
typedef  int RLIM_TYPE ;

/* Variables and functions */
 scalar_t__ RLIMIT_CPU ; 
 scalar_t__ RLIMIT_DATA ; 
 scalar_t__ RLIMIT_FSIZE ; 
 int RLIM_INFINITY ; 
 int /*<<< orphan*/  getrlimit (scalar_t__,struct rlimit*) ; 
 int /*<<< orphan*/  psecs (int) ; 
 int ulimit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,...) ; 
 int /*<<< orphan*/  xputchar (char) ; 

__attribute__((used)) static void
plim(struct limits *lp, int hard)
{
# ifdef BSDLIMIT
    struct rlimit rlim;
# endif /* BSDLIMIT */
    RLIM_TYPE limit;
    int     xdiv = lp->limdiv;

    xprintf("%-13.13s", lp->limname);

# ifndef BSDLIMIT
    limit = ulimit(lp->limconst, 0);
#  ifdef aiws
    if (lp->limconst == RLIMIT_DATA)
	limit -= 0x20000000;
#  endif /* aiws */
# else /* BSDLIMIT */
    (void) getrlimit(lp->limconst, &rlim);
    limit = hard ? rlim.rlim_max : rlim.rlim_cur;
# endif /* BSDLIMIT */

# if !defined(BSDLIMIT) || defined(FILESIZE512)
    /*
     * Christos: filesize comes in 512 blocks. we divide by 2 to get 1024
     * blocks. Note we cannot pre-multiply cause we might overflow (A/UX)
     */
    if (lp->limconst == RLIMIT_FSIZE) {
	if (limit >= (RLIM_INFINITY / 512))
	    limit = RLIM_INFINITY;
	else
	    xdiv = (xdiv == 1024 ? 2 : 1);
    }
# endif /* !BSDLIMIT || FILESIZE512 */

    if (limit == RLIM_INFINITY)
	xprintf("unlimited");
    else
# if defined(RLIMIT_CPU) && defined(_OSD_POSIX)
    if (lp->limconst == RLIMIT_CPU &&
        (unsigned long)limit >= 0x7ffffffdUL)
	xprintf("unlimited");
    else
# endif
# ifdef RLIMIT_CPU
    if (lp->limconst == RLIMIT_CPU)
	psecs(limit);
    else
# endif /* RLIMIT_CPU */
	xprintf("%ld %s", (long) (limit / xdiv), lp->limscale);
    xputchar('\n');
}
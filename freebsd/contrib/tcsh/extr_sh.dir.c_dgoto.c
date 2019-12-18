#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* di_name; } ;
typedef  char Char ;

/* Variables and functions */
 scalar_t__ ABSOLUTEP (char*) ; 
 int /*<<< orphan*/  Strcpy (char*,char*) ; 
 size_t Strlen (char*) ; 
 char* agetcwd () ; 
 int /*<<< orphan*/  cleanup_ignore (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* dcanon (char*,char*) ; 
 TYPE_1__* dcwd ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static Char *
dgoto(Char *cp)
{
    Char *dp, *ret;

    if (!ABSOLUTEP(cp))
    {
	Char *p, *q;
	size_t cwdlen;

	cwdlen = Strlen(dcwd->di_name);
	if (cwdlen == 1)	/* root */
	    cwdlen = 0;
	dp = xmalloc((cwdlen + Strlen(cp) + 2) * sizeof(Char));
	for (p = dp, q = dcwd->di_name; (*p++ = *q++) != '\0';)
	    continue;
	if (cwdlen)
	    p[-1] = '/';
	else
	    p--;		/* don't add a / after root */
	Strcpy(p, cp);
	xfree(cp);
	cp = dp;
	dp += cwdlen;
    }
    else
	dp = cp;

#if defined(WINNT_NATIVE)
    return agetcwd();
#elif defined(__CYGWIN__)
    if (ABSOLUTEP(cp) && cp[1] == ':') { /* Only DOS paths are treated that way */
	return agetcwd();
    } else {
	cleanup_push(cp, xfree);
    	ret = dcanon(cp, dp);
	cleanup_ignore(cp);
	cleanup_until(cp);
    }
#else /* !WINNT_NATIVE */
    cleanup_push(cp, xfree);
    ret = dcanon(cp, dp);
    cleanup_ignore(cp);
    cleanup_until(cp);
#endif /* WINNT_NATIVE */
    return ret;
}
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
struct limits {float limdiv; int /*<<< orphan*/  limconst; } ;
typedef  scalar_t__ RLIM_TYPE ;
typedef  char Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_SCALEF ; 
 int ERR_TOOLARGE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 scalar_t__ Isdigit (char) ; 
 int /*<<< orphan*/  RLIMIT_CPU ; 
 scalar_t__ RLIM_INFINITY ; 
 float atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  limtail (char*,char*) ; 
 int /*<<< orphan*/  limtail2 (char*,char*,char*) ; 
 scalar_t__ restrict_limit (float) ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  stderror (int) ; 

__attribute__((used)) static  RLIM_TYPE
getval(struct limits *lp, Char **v)
{
    float f;
    Char   *cp = *v++;

    f = atof(short2str(cp));

# ifdef convex
    /*
     * is f too large to cope with. limit f to minint, maxint  - X-6768 by
     * strike
     */
    if ((f < (double) INT_MIN) || (f > (double) INT_MAX)) {
	stderror(ERR_NAME | ERR_TOOLARGE);
    }
# endif /* convex */

    while (Isdigit(*cp) || *cp == '.' || *cp == 'e' || *cp == 'E')
	cp++;
    if (*cp == 0) {
	if (*v == 0)
	    return restrict_limit((f * lp->limdiv) + 0.5);
	cp = *v;
    }
    switch (*cp) {
# ifdef RLIMIT_CPU
    case ':':
	if (lp->limconst != RLIMIT_CPU)
	    goto badscal;
	return f == 0.0 ? (RLIM_TYPE) 0 : restrict_limit((f * 60.0 + atof(short2str(cp + 1))));
    case 'h':
	if (lp->limconst != RLIMIT_CPU)
	    goto badscal;
	limtail(cp, "hours");
	f *= 3600.0;
	break;
# endif /* RLIMIT_CPU */
    case 'm':
# ifdef RLIMIT_CPU
	if (lp->limconst == RLIMIT_CPU) {
	    limtail(cp, "minutes");
	    f *= 60.0;
	    break;
	}
# endif /* RLIMIT_CPU */
	limtail2(cp, "megabytes", "mbytes");
	f *= 1024.0 * 1024.0;
	break;
# ifdef RLIMIT_CPU
    case 's':
	if (lp->limconst != RLIMIT_CPU)
	    goto badscal;
	limtail(cp, "seconds");
	break;
# endif /* RLIMIT_CPU */
    case 'G':
	*cp = 'g';
	/*FALLTHROUGH*/
    case 'g':
# ifdef RLIMIT_CPU
	if (lp->limconst == RLIMIT_CPU)
	    goto badscal;
# endif /* RLIMIT_CPU */
	limtail2(cp, "gigabytes", "gbytes");
	f *= 1024.0 * 1024.0 * 1024.0;
	break;
    case 'M':
# ifdef RLIMIT_CPU
	if (lp->limconst == RLIMIT_CPU)
	    goto badscal;
# endif /* RLIMIT_CPU */
	*cp = 'm';
	limtail2(cp, "megabytes", "mbytes");
	f *= 1024.0 * 1024.0;
	break;
    case 'k':
# ifdef RLIMIT_CPU
	if (lp->limconst == RLIMIT_CPU)
	    goto badscal;
# endif /* RLIMIT_CPU */
	limtail2(cp, "kilobytes", "kbytes");
	f *= 1024.0;
	break;
    case 'b':
# ifdef RLIMIT_CPU
	if (lp->limconst == RLIMIT_CPU)
	    goto badscal;
# endif /* RLIMIT_CPU */
	limtail(cp, "blocks");
	f *= 512.0;
	break;
    case 'u':
	limtail(cp, "unlimited");
	return ((RLIM_TYPE) RLIM_INFINITY);
    default:
# ifdef RLIMIT_CPU
badscal:
# endif /* RLIMIT_CPU */
	stderror(ERR_NAME | ERR_SCALEF);
    }
# ifdef convex
    return f == 0.0 ? (RLIM_TYPE) 0 : restrict_limit((f + 0.5));
# else
    f += 0.5;
    if (f > (float) ((RLIM_TYPE) RLIM_INFINITY))
	return ((RLIM_TYPE) RLIM_INFINITY);
    else
	return ((RLIM_TYPE) f);
# endif /* convex */
}
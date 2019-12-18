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
typedef  long rlim_t ;

/* Variables and functions */
#define  RLIMIT_CORE 142 
#define  RLIMIT_CPU 141 
#define  RLIMIT_DATA 140 
#define  RLIMIT_FSIZE 139 
#define  RLIMIT_KQUEUES 138 
#define  RLIMIT_MEMLOCK 137 
#define  RLIMIT_NOFILE 136 
#define  RLIMIT_NPROC 135 
#define  RLIMIT_NPTS 134 
#define  RLIMIT_RSS 133 
#define  RLIMIT_SBSIZE 132 
#define  RLIMIT_STACK 131 
#define  RLIMIT_SWAP 130 
#define  RLIMIT_UMTXP 129 
#define  RLIMIT_VMEM 128 
 long RLIM_INFINITY ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 long strtoq (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,int,char const*) ; 

__attribute__((used)) static rlim_t
resource_num(int which, int ch, const char *str)
{
    rlim_t res = RLIM_INFINITY;

    if (str != NULL &&
	!(strcasecmp(str, "inf") == 0 ||
	  strcasecmp(str, "infinity") == 0 ||
	  strcasecmp(str, "unlimit") == 0 ||
	  strcasecmp(str, "unlimited") == 0)) {
	const char * s = str;
	char *e;

	switch (which) {
	case RLIMIT_CPU:	/* time values */
	    errno = 0;
	    res = 0;
	    while (*s) {
		rlim_t tim = strtoq(s, &e, 0);
		if (e == NULL || e == s || errno)
		    break;
		switch (*e++) {
		case 0:		   	/* end of string */
		    e--;
		default:
		case 's': case 'S':	/* seconds */
		    break;
		case 'm': case 'M':	/* minutes */
		    tim *= 60L;
		    break;
		case 'h': case 'H':	/* hours */
		    tim *= (60L * 60L);
		    break;
		case 'd': case 'D':	/* days */
		    tim *= (60L * 60L * 24L);
		    break;
		case 'w': case 'W':	/* weeks */
		    tim *= (60L * 60L * 24L * 7L);
		    break;
		case 'y': case 'Y':	/* Years */
		    tim *= (60L * 60L * 24L * 365L);
		}
		s = e;
		res += tim;
	    }
	    break;
	case RLIMIT_FSIZE: /* Size values */
	case RLIMIT_DATA:
	case RLIMIT_STACK:
	case RLIMIT_CORE:
	case RLIMIT_RSS:
	case RLIMIT_MEMLOCK:
	case RLIMIT_SBSIZE:
	case RLIMIT_VMEM:
	case RLIMIT_SWAP:
	    errno = 0;
	    res = 0;
	    while (*s) {
		rlim_t mult, tim = strtoq(s, &e, 0);
		if (e == NULL || e == s || errno)
		    break;
		switch (*e++) {
		case 0:	/* end of string */
		    e--;
		default:
		    mult = 1;
		    break;
		case 'b': case 'B':	/* 512-byte blocks */
		    mult = 512;
		    break;
		case 'k': case 'K':	/* 1024-byte Kilobytes */
		    mult = 1024;
		    break;
		case 'm': case 'M':	/* 1024-k kbytes */
		    mult = 1024 * 1024;
		    break;
		case 'g': case 'G':	/* 1Gbyte */
		    mult = 1024 * 1024 * 1024;
		    break;
		case 't': case 'T':	/* 1TBte */
		    mult = 1024LL * 1024LL * 1024LL * 1024LL;
		    break;
		}
		s = e;
		res += (tim * mult);
	    }
	    break;
	case RLIMIT_NPROC:
	case RLIMIT_NOFILE:
	case RLIMIT_NPTS:
	case RLIMIT_KQUEUES:
	case RLIMIT_UMTXP:
	    res = strtoq(s, &e, 0);
	    s = e;
	    break;
	}
	if (*s) {
	    warnx("invalid value -%c `%s'", ch, str);
	    usage();
	}
    }
    return res;
}
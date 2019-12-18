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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  EINVAL ; 
#define  _CS_PATH 141 
#define  _CS_POSIX_V6_ILP32_OFF32_CFLAGS 140 
#define  _CS_POSIX_V6_ILP32_OFF32_LDFLAGS 139 
#define  _CS_POSIX_V6_ILP32_OFF32_LIBS 138 
#define  _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS 137 
#define  _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS 136 
#define  _CS_POSIX_V6_ILP32_OFFBIG_LIBS 135 
#define  _CS_POSIX_V6_LP64_OFF64_CFLAGS 134 
#define  _CS_POSIX_V6_LP64_OFF64_LDFLAGS 133 
#define  _CS_POSIX_V6_LP64_OFF64_LIBS 132 
#define  _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS 131 
#define  _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS 130 
#define  _CS_POSIX_V6_LPBIG_OFFBIG_LIBS 129 
#define  _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS 128 
 char* _PATH_STDPATH ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

size_t
confstr(int name, char *buf, size_t len)
{
	const char *p;
	const char UPE[] = "unsupported programming environment";

	switch (name) {
	case _CS_PATH:
		p = _PATH_STDPATH;
		goto docopy;

		/*
		 * POSIX/SUS ``Programming Environments'' stuff
		 *
		 * We don't support more than one programming environment
		 * on any platform (yet), so we just return the empty
		 * string for the environment we are compiled for,
		 * and the string "unsupported programming environment"
		 * for anything else.  (The Standard says that if these
		 * values are used on a system which does not support
		 * this environment -- determined via sysconf() -- then
		 * the value we return is unspecified.  So, we return
		 * something which will cause obvious breakage.)
		 */
	case _CS_POSIX_V6_ILP32_OFF32_CFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_LDFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_LIBS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LIBS:
		/*
		 * These two environments are never supported.
		 */
		p = UPE;
		goto docopy;

	case _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LIBS:
		if (sizeof(long) * CHAR_BIT == 32 &&
		    sizeof(off_t) > sizeof(long))
			p = "";
		else
			p = UPE;
		goto docopy;

	case _CS_POSIX_V6_LP64_OFF64_CFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_LDFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_LIBS:
		if (sizeof(long) * CHAR_BIT >= 64 &&
		    sizeof(void *) * CHAR_BIT >= 64 &&
		    sizeof(int) * CHAR_BIT >= 32 &&
		    sizeof(off_t) >= sizeof(long))
			p = "";
		else
			p = UPE;
		goto docopy;

	case _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS:
		/* XXX - should have more complete coverage */
		if (sizeof(long) * CHAR_BIT >= 64)
			p = "_POSIX_V6_LP64_OFF64";
		else
			p = "_POSIX_V6_ILP32_OFFBIG";
		goto docopy;

docopy:
		if (len != 0 && buf != NULL)
			strlcpy(buf, p, len);
		return (strlen(p) + 1);

	default:
		errno = EINVAL;
		return (0);
	}
	/* NOTREACHED */
}
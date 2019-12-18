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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 unsigned long long strtoull (char*,char**,int) ; 
 int tolower (char) ; 

__attribute__((used)) static unsigned long long
getsize(char *s)
{
	int sh;
	unsigned long long length;
	char *suffix;

	/*
	 * NOTE: We don't handle 'Z' (zetta) or 'Y' (yotta) suffixes yet.
	 * These are too large to store in unsigned long long (64bits).
	 * In the future, we'll have to use larger type,
	 * something like uint128_t.
	 */
	length = strtoull(s, &suffix, 10);
	sh = 0;
	switch (tolower(*suffix)) {
	case 'e':	/* Exabytes. */
		sh = 60;
		break;
	case 'p':	/* Petabytes. */
		sh = 50;
		break;
	case 't':	/* Terabytes. */
		sh = 40;
		break;
	case 'g':	/* Gigabytes. */
		sh = 30;
		break;
	case 'm':	/* Megabytes. */
		sh = 20;
		break;
	case 'k':	/* Kilobytes. */
		sh = 10;
		break;
	case 'b':	/* Blocks. */
		sh = 9;
		break;
	case '\0':	/* Bytes. */
		break;
	default:	/* Unknown... */
		errno = EINVAL;
		return 0;
	}
	if (sh) {
		unsigned long long l;

		l = length;
		length <<= sh;
		/* Check overflow. */
		if ((length >> sh) != l) {
			errno = ERANGE;
			return 0;
		}
	}

	return length;
}
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
typedef  scalar_t__ uintmax_t ;
typedef  unsigned int uint64_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ UINT64_MAX ; 
 int errno ; 
 scalar_t__ strtoumax (char const*,char**,int /*<<< orphan*/ ) ; 
 int tolower (unsigned char) ; 

int
expand_number(const char *buf, uint64_t *num)
{
	char *endptr;
	uintmax_t umaxval;
	uint64_t number;
	unsigned shift;
	int serrno;

	serrno = errno;
	errno = 0;
	umaxval = strtoumax(buf, &endptr, 0);
	if (umaxval > UINT64_MAX)
		errno = ERANGE;
	if (errno != 0)
		return (-1);
	errno = serrno;
	number = umaxval;

	switch (tolower((unsigned char)*endptr)) {
	case 'e':
		shift = 60;
		break;
	case 'p':
		shift = 50;
		break;
	case 't':
		shift = 40;
		break;
	case 'g':
		shift = 30;
		break;
	case 'm':
		shift = 20;
		break;
	case 'k':
		shift = 10;
		break;
	case 'b':
	case '\0': /* No unit. */
		*num = number;
		return (0);
	default:
		/* Unrecognized unit. */
		errno = EINVAL;
		return (-1);
	}

	if ((number << shift) >> shift != number) {
		/* Overflow */
		errno = ERANGE;
		return (-1);
	}
	*num = number << shift;
	return (0);
}
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
typedef  int off_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int OFF_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strtoimax (char const*,char**,int /*<<< orphan*/ ) ; 

int
g_parse_lba(const char *lbastr, unsigned int sectorsize, off_t *sectors)
{
	off_t number, mult, unit;
	char *s;

	assert(lbastr != NULL);
	assert(sectorsize > 0);
	assert(sectors != NULL);

	number = (off_t)strtoimax(lbastr, &s, 0);
	if (s == lbastr || number < 0)
		return (EINVAL);

	mult = 1;
	unit = sectorsize;
	if (*s == '\0')
		goto done;
	switch (*s) {
	case 'e': case 'E':
		mult *= 1024;
		/* FALLTHROUGH */
	case 'p': case 'P':
		mult *= 1024;
		/* FALLTHROUGH */
	case 't': case 'T':
		mult *= 1024;
		/* FALLTHROUGH */
	case 'g': case 'G':
		mult *= 1024;
		/* FALLTHROUGH */
	case 'm': case 'M':
		mult *= 1024;
		/* FALLTHROUGH */
	case 'k': case 'K':
		mult *= 1024;
		break;
	default:
		goto sfx;
	}
	unit = 1;	/* bytes */
	s++;
	if (*s == '\0')
		goto done;
sfx:
	switch (*s) {
	case 's': case 'S':
		unit = sectorsize;	/* sector */
		break;
	case 'b': case 'B':
		unit = 1;		/* bytes */
		break;
	default:
		return (EINVAL);
	}
	s++;
	if (*s != '\0')
		return (EINVAL);
done:
	if ((OFF_MAX / unit) < mult || (OFF_MAX / mult / unit) < number)
		return (ERANGE);
	number *= mult * unit;
	if (number % sectorsize)
		return (EINVAL);
	number /= sectorsize;
	*sectors = number;
	return (0);
}
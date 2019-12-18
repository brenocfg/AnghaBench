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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  KENV_MNAMELEN ; 
 scalar_t__ KENV_MVALLEN ; 
 int SCHAR_MAX ; 
 int SCHAR_MIN ; 
 int SHRT_MAX ; 
 int SHRT_MIN ; 
 int UCHAR_MAX ; 
 int UINT_MAX ; 
 int USHRT_MAX ; 
 scalar_t__ getenv_string (char const*,char*,int) ; 
 int strtoq (char*,char**,int /*<<< orphan*/ ) ; 

int
getenv_array(const char *name, void *pdata, int size, int *psize,
    int type_size, bool allow_signed)
{
	char buf[KENV_MNAMELEN + 1 + KENV_MVALLEN + 1];
	uint8_t shift;
	int64_t value;
	int64_t old;
	char *end;
	char *ptr;
	int n;

	if (getenv_string(name, buf, sizeof(buf)) == 0)
		return (0);

	/* get maximum number of elements */
	size /= type_size;

	n = 0;

	for (ptr = buf; *ptr != 0; ) {

		value = strtoq(ptr, &end, 0);

		/* check if signed numbers are allowed */
		if (value < 0 && !allow_signed)
			goto error;

		/* check for invalid value */
		if (ptr == end)
			goto error;
		
		/* check for valid suffix */
		switch (*end) {
		case 't':
		case 'T':
			shift = 40;
			end++;
			break;
		case 'g':
		case 'G':
			shift = 30;
			end++;
			break;
		case 'm':
		case 'M':
			shift = 20;
			end++;
			break;
		case 'k':
		case 'K':
			shift = 10;
			end++;
			break;
		case ' ':
		case '\t':
		case ',':
		case 0:
			shift = 0;
			break;
		default:
			/* garbage after numeric value */
			goto error;
		}

		/* skip till next value, if any */
		while (*end == '\t' || *end == ',' || *end == ' ')
			end++;

		/* update pointer */
		ptr = end;

		/* apply shift */
		old = value;
		value <<= shift;

		/* overflow check */
		if ((value >> shift) != old)
			goto error;

		/* check for buffer overflow */
		if (n >= size)
			goto error;

		/* store value according to type size */
		switch (type_size) {
		case 1:
			if (allow_signed) {
				if (value < SCHAR_MIN || value > SCHAR_MAX)
					goto error;
			} else {
				if (value < 0 || value > UCHAR_MAX)
					goto error;
			}
			((uint8_t *)pdata)[n] = (uint8_t)value;
			break;
		case 2:
			if (allow_signed) {
				if (value < SHRT_MIN || value > SHRT_MAX)
					goto error;
			} else {
				if (value < 0 || value > USHRT_MAX)
					goto error;
			}
			((uint16_t *)pdata)[n] = (uint16_t)value;
			break;
		case 4:
			if (allow_signed) {
				if (value < INT_MIN || value > INT_MAX)
					goto error;
			} else {
				if (value > UINT_MAX)
					goto error;
			}
			((uint32_t *)pdata)[n] = (uint32_t)value;
			break;
		case 8:
			((uint64_t *)pdata)[n] = (uint64_t)value;
			break;
		default:
			goto error;
		}
		n++;
	}
	*psize = n * type_size;

	if (n != 0)
		return (1);	/* success */
error:
	return (0);	/* failure */
}
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
 size_t os_strlen (char const*) ; 

size_t utf8_unescape(const char *inp, size_t in_size,
		     char *outp, size_t out_size)
{
	size_t res_size = 0;

	if (!inp || !outp)
		return 0;

	if (!in_size)
		in_size = os_strlen(inp);

	/* Advance past leading single quote */
	if (*inp == '\'' && in_size) {
		inp++;
		in_size--;
	}

	while (in_size) {
		in_size--;
		if (res_size >= out_size)
			return 0;

		switch (*inp) {
		case '\'':
			/* Terminate on bare single quote */
			*outp = '\0';
			return res_size;

		case '\\':
			if (!in_size)
				return 0;
			in_size--;
			inp++;
			/* fall through */

		default:
			*outp++ = *inp++;
			res_size++;
		}
	}

	/* NUL terminate if space allows */
	if (res_size < out_size)
		*outp = '\0';

	return res_size;
}
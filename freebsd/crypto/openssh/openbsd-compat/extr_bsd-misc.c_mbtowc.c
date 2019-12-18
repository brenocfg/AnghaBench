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
typedef  char wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  errno ; 

int
mbtowc(wchar_t *pwc, const char *s, size_t n)
{
	if (s == NULL || *s == '\0')
		return 0;	/* ASCII is not state-dependent */
	if (*s < 0 || *s > 0x7f || n < 1) {
		errno = EOPNOTSUPP;
		return -1;
	}
	if (pwc != NULL)
		*pwc = *s;
	return 1;
}
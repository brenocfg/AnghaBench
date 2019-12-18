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
 char* strchr (char const*,char const) ; 

__attribute__((used)) static int
roff_evalstrcond(const char *v, int *pos)
{
	const char	*s1, *s2, *s3;
	int		 match;

	match = 0;
	s1 = v + *pos;		/* initial delimiter */
	s2 = s1 + 1;		/* for scanning the first string */
	s3 = strchr(s2, *s1);	/* for scanning the second string */

	if (NULL == s3)		/* found no middle delimiter */
		goto out;

	while ('\0' != *++s3) {
		if (*s2 != *s3) {  /* mismatch */
			s3 = strchr(s3, *s1);
			break;
		}
		if (*s3 == *s1) {  /* found the final delimiter */
			match = 1;
			break;
		}
		s2++;
	}

out:
	if (NULL == s3)
		s3 = strchr(s2, '\0');
	else if (*s3 != '\0')
		s3++;
	*pos = s3 - v;
	return match;
}
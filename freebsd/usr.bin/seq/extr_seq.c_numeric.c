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
 scalar_t__ ISEXP (unsigned char) ; 
 scalar_t__ ISSIGN (unsigned char) ; 
 int /*<<< orphan*/  decimal_point ; 
 scalar_t__ isdigit (unsigned char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
numeric(const char *s)
{
	int seen_decimal_pt, decimal_pt_len;

	/* skip any sign */
	if (ISSIGN((unsigned char)*s))
		s++;

	seen_decimal_pt = 0;
	decimal_pt_len = strlen(decimal_point);
	while (*s) {
		if (!isdigit((unsigned char)*s)) {
			if (!seen_decimal_pt &&
			    strncmp(s, decimal_point, decimal_pt_len) == 0) {
				s += decimal_pt_len;
				seen_decimal_pt = 1;
				continue;
			}
			if (ISEXP((unsigned char)*s)) {
				s++;
				if (ISSIGN((unsigned char)*s) ||
				    isdigit((unsigned char)*s)) {
					s++;
					continue;
				}
			}
			break;
		}
		s++;
	}
	return (*s == '\0');
}
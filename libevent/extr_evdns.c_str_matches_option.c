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
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static inline int
str_matches_option(const char *s1, const char *optionname)
{
	/* Option names are given as "option:" We accept either 'option' in
	 * s1, or 'option:randomjunk'.  The latter form is to implement the
	 * resolv.conf parser. */
	size_t optlen = strlen(optionname);
	size_t slen = strlen(s1);
	if (slen == optlen || slen == optlen - 1)
		return !strncmp(s1, optionname, slen);
	else if (slen > optlen)
		return !strncmp(s1, optionname, optlen);
	else
		return 0;
}
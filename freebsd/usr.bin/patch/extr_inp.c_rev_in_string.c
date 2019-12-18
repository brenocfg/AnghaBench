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
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/ * revision ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strnEQ (char const*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bool
rev_in_string(const char *string)
{
	const char	*s;
	size_t		patlen;

	if (revision == NULL)
		return true;
	patlen = strlen(revision);
	if (strnEQ(string, revision, patlen) && isspace((unsigned char)string[patlen]))
		return true;
	for (s = string; *s; s++) {
		if (isspace((unsigned char)*s) && strnEQ(s + 1, revision, patlen) &&
		    isspace((unsigned char)s[patlen + 1])) {
			return true;
		}
	}
	return false;
}
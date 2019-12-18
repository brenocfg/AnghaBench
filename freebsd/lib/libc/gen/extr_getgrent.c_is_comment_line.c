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
 int /*<<< orphan*/  isspace (unsigned char) ; 

__attribute__((used)) static int
is_comment_line(const char *s, size_t n)
{
	const char	*eom;

	eom = &s[n];

	for (; s < eom; s++)
		if (*s == '#' || !isspace((unsigned char)*s))
			break;
	return (*s == '#' || s == eom);
}
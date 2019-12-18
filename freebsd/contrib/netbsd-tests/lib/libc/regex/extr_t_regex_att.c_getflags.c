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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int /*<<< orphan*/ ,char*,char) ; 
 int REG_ICASE ; 

__attribute__((used)) static int
getflags(char *s)
{
	int flags = 0;

	for (;; s++)
		switch (*s) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			*s = '\0';
			break;
		case '\0':
			return flags;
		case 'B':
		case 'E':
		case 'F':
		case 'L':
			break;
		case 'i':
			flags |= REG_ICASE;
			*s = '\0';
			break;
		case '$':
			*s = '\0';
			break;
		case 'n':
			*s = '\0';
			break;
		default:
			ATF_REQUIRE_MSG(0, "Unknown char %c", *s);
			break;
		}
}
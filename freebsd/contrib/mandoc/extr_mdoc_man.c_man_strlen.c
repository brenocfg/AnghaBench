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
#define  ESCAPE_ERROR 134 
#define  ESCAPE_NUMBERED 133 
#define  ESCAPE_OVERSTRIKE 132 
#define  ESCAPE_SKIPCHAR 131 
#define  ESCAPE_SPECIAL 130 
#define  ESCAPE_UNDEF 129 
#define  ESCAPE_UNICODE 128 
 int mandoc_escape (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static int
man_strlen(const char *cp)
{
	size_t	 rsz;
	int	 skip, sz;

	sz = 0;
	skip = 0;
	for (;;) {
		rsz = strcspn(cp, "\\");
		if (rsz) {
			cp += rsz;
			if (skip) {
				skip = 0;
				rsz--;
			}
			sz += rsz;
		}
		if ('\0' == *cp)
			break;
		cp++;
		switch (mandoc_escape(&cp, NULL, NULL)) {
		case ESCAPE_ERROR:
			return sz;
		case ESCAPE_UNICODE:
		case ESCAPE_NUMBERED:
		case ESCAPE_SPECIAL:
		case ESCAPE_UNDEF:
		case ESCAPE_OVERSTRIKE:
			if (skip)
				skip = 0;
			else
				sz++;
			break;
		case ESCAPE_SKIPCHAR:
			skip = 1;
			break;
		default:
			break;
		}
	}
	return sz;
}
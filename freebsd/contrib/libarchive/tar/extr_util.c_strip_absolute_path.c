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
struct bsdtar {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  warn_strip_drive_letter (struct bsdtar*) ; 
 int /*<<< orphan*/  warn_strip_leading_char (struct bsdtar*,char const*) ; 

__attribute__((used)) static const char*
strip_absolute_path(struct bsdtar *bsdtar, const char *p)
{
	const char *rp;

	/* Remove leading "//./" or "//?/" or "//?/UNC/"
	 * (absolute path prefixes used by Windows API) */
	if ((p[0] == '/' || p[0] == '\\') &&
	    (p[1] == '/' || p[1] == '\\') &&
	    (p[2] == '.' || p[2] == '?') &&
	    (p[3] == '/' || p[3] == '\\'))
	{
		if (p[2] == '?' &&
		    (p[4] == 'U' || p[4] == 'u') &&
		    (p[5] == 'N' || p[5] == 'n') &&
		    (p[6] == 'C' || p[6] == 'c') &&
		    (p[7] == '/' || p[7] == '\\'))
			p += 8;
		else
			p += 4;
		warn_strip_drive_letter(bsdtar);
	}

	/* Remove multiple leading slashes and Windows drive letters. */
	do {
		rp = p;
		if (((p[0] >= 'a' && p[0] <= 'z') ||
		     (p[0] >= 'A' && p[0] <= 'Z')) &&
		    p[1] == ':') {
			p += 2;
			warn_strip_drive_letter(bsdtar);
		}

		/* Remove leading "/../", "/./", "//", etc. */
		while (p[0] == '/' || p[0] == '\\') {
			if (p[1] == '.' &&
			    p[2] == '.' &&
			    (p[3] == '/' || p[3] == '\\')) {
				p += 3; /* Remove "/..", leave "/" for next pass. */
			} else if (p[1] == '.' &&
				   (p[2] == '/' || p[2] == '\\')) {
				p += 2; /* Remove "/.", leave "/" for next pass. */
			} else
				p += 1; /* Remove "/". */
			warn_strip_leading_char(bsdtar, rp);
		}
	} while (rp != p);

	return (p);
}
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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perr (char*,...) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

const char *
devcheck(const char *origname)
{
	struct stat stslash, stchar;

	if (stat("/", &stslash) < 0) {
		perr("Can't stat `/'");
		return (origname);
	}
	if (stat(origname, &stchar) < 0) {
		perr("Can't stat %s\n", origname);
		return (origname);
	}
	if (!S_ISCHR(stchar.st_mode)) {
		perr("%s is not a char device\n", origname);
	}
	return (origname);
}
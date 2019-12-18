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
struct stat {int st_mode; } ;

/* Variables and functions */
 int S_ISUID ; 
 int /*<<< orphan*/  fpath ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,char*) ; 

__attribute__((used)) static void
confirm_sugid(char *test_case, int asroot, int injail)
{
	struct stat sb;

	if (stat(fpath, &sb) < 0) {
		warn("%s stat(%s)", test_case, fpath);
		return;
	}
	if (asroot) {
		if (!(sb.st_mode & S_ISUID))
			warnx("%s(root, %s): !SUID", test_case, injail ?
			    "jail" : "!jail");
	} else {
		if (sb.st_mode & S_ISUID)
			warnx("%s(!root, %s): SUID", test_case, injail ?
			    "jail" : "!jail");
	}
}
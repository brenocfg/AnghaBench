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
struct passwd {int pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_NOUSER ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
parse_uid(const char *s, char *buf, size_t bufsize)
{
	struct passwd  *pw;
	char *inval;

	if ((pw = getpwnam(s)) != NULL)
		snprintf(buf, bufsize, "%d", pw->pw_uid);
	else {
		strtol(s, &inval, 10);
		if (*inval != 0) {
                       errx(EX_NOUSER, "unknown user id: %s", s);
                       usage();
		} else {
			strncpy(buf, s, bufsize);
		}
	}
}
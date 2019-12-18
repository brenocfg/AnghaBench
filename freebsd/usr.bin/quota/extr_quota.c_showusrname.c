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
struct passwd {int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  USRQUOTA ; 
 struct passwd* getpwnam (char*) ; 
 int showquotas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
showusrname(char *name)
{
	struct passwd *pwd = getpwnam(name);

	if (pwd == NULL) {
		warnx("%s: unknown user", name);
		return(1);
	}
	return(showquotas(USRQUOTA, pwd->pw_uid, name));
}
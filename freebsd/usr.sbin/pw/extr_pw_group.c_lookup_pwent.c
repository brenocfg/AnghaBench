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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_NOUSER ; 
 struct passwd* GETPWNAM (char const*) ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 

__attribute__((used)) static struct passwd *
lookup_pwent(const char *user)
{
	struct passwd *pwd;

	if ((pwd = GETPWNAM(user)) == NULL &&
	    (!isdigit((unsigned char)*user) ||
	    (pwd = getpwuid((uid_t) atoi(user))) == NULL))
		errx(EX_NOUSER, "user `%s' does not exist", user);

	return (pwd);
}
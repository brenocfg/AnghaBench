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
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  id (char const*,char*) ; 
 int /*<<< orphan*/  uid ; 

__attribute__((used)) static void
a_uid(const char *s)
{
	struct passwd *pw;

	if (*s == '\0')			/* Argument was "[:.]gid". */
		return;
	uid = ((pw = getpwnam(s)) != NULL) ? pw->pw_uid : id(s, "user");
}
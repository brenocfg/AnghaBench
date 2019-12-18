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
struct group {int /*<<< orphan*/  gr_gid; } ;

/* Variables and functions */
 struct group* getgrnam (char const*) ; 
 int /*<<< orphan*/  gid ; 
 char const* gname ; 
 int /*<<< orphan*/  id (char const*,char*) ; 

__attribute__((used)) static void
a_gid(const char *s)
{
	struct group *gr;

	if (*s == '\0')			/* Argument was "uid[:.]". */
		return;
	gname = s;
	gid = ((gr = getgrnam(s)) != NULL) ? gr->gr_gid : id(s, "group");
}
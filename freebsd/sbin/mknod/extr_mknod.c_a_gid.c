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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct group* getgrnam (char const*) ; 
 int /*<<< orphan*/  id (char const*,char*) ; 

__attribute__((used)) static gid_t
a_gid(const char *s)
{
	struct group *gr;

	if (*s == '\0')			/* Argument was "uid[:.]". */
		errx(1, "group must be specified when the owner is");
	return ((gr = getgrnam(s)) == NULL) ? id(s, "group") : gr->gr_gid;
}
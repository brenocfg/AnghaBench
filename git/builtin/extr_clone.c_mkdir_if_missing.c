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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mkdir (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static void mkdir_if_missing(const char *pathname, mode_t mode)
{
	struct stat st;

	if (!mkdir(pathname, mode))
		return;

	if (errno != EEXIST)
		die_errno(_("failed to create directory '%s'"), pathname);
	else if (stat(pathname, &st))
		die_errno(_("failed to stat '%s'"), pathname);
	else if (!S_ISDIR(st.st_mode))
		die(_("%s exists and is not a directory"), pathname);
}
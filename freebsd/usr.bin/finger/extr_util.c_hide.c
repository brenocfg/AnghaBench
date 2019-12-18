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
struct stat {int dummy; } ;
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char* _PATH_NOFINGER ; 
 scalar_t__ invoker_root ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int
hide(struct passwd *pw)
{
	struct stat st;
	char buf[MAXPATHLEN];

	if (invoker_root || !pw->pw_dir)
		return 0;

	snprintf(buf, sizeof(buf), "%s/%s", pw->pw_dir, _PATH_NOFINGER);

	if (stat(buf, &st) == 0)
		return 1;

	return 0;
}
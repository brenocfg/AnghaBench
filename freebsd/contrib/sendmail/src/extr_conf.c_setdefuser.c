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
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  defuserbuf ;

/* Variables and functions */
 scalar_t__ DefUid ; 
 char* DefUser ; 
 int /*<<< orphan*/  sm_dprintf (char*,long,char*) ; 
 struct passwd* sm_getpwuid (scalar_t__) ; 
 int /*<<< orphan*/  sm_strlcpy (char*,char*,int) ; 
 scalar_t__ tTd (int,int) ; 

void
setdefuser()
{
	struct passwd *defpwent;
	static char defuserbuf[40];

	DefUser = defuserbuf;
	defpwent = sm_getpwuid(DefUid);
	(void) sm_strlcpy(defuserbuf,
			  (defpwent == NULL || defpwent->pw_name == NULL)
			   ? "nobody" : defpwent->pw_name,
			  sizeof(defuserbuf));
	if (tTd(37, 4))
		sm_dprintf("setdefuser: DefUid=%ld, DefUser=%s\n",
			   (long) DefUid, DefUser);
}
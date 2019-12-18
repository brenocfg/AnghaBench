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
typedef  scalar_t__ uid_t ;
struct passwd {char* pw_name; scalar_t__ pw_uid; } ;

/* Variables and functions */
 scalar_t__ RealUid ; 
 char* addquotes (char*,int /*<<< orphan*/ *) ; 
 struct passwd* sm_getpwnam (char*) ; 
 struct passwd* sm_getpwuid (scalar_t__) ; 
 char* sm_pstrdup_x (char*) ; 
 int /*<<< orphan*/ * strpbrk (char*,char*) ; 
 int /*<<< orphan*/  syserr (char*) ; 

char *
username()
{
	static char *myname = NULL;
	extern char *getlogin();
	register struct passwd *pw;

	/* cache the result */
	if (myname == NULL)
	{
		myname = getlogin();
		if (myname == NULL || myname[0] == '\0')
		{
			pw = sm_getpwuid(RealUid);
			if (pw != NULL)
				myname = pw->pw_name;
		}
		else
		{
			uid_t uid = RealUid;

			if ((pw = sm_getpwnam(myname)) == NULL ||
			      (uid != 0 && uid != pw->pw_uid))
			{
				pw = sm_getpwuid(uid);
				if (pw != NULL)
					myname = pw->pw_name;
			}
		}
		if (myname == NULL || myname[0] == '\0')
		{
			syserr("554 5.3.0 Who are you?");
			myname = "postmaster";
		}
		else if (strpbrk(myname, ",;:/|\"\\") != NULL)
			myname = addquotes(myname, NULL);
		else
			myname = sm_pstrdup_x(myname);
	}
	return myname;
}
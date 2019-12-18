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
typedef  int uid_t ;
struct user {char* name; int uid; } ;
struct passwd {int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct passwd* getpwuid (int) ; 
 scalar_t__ malloc (int) ; 
 int nusers ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 struct user* users ; 
 int /*<<< orphan*/  usrrehash () ; 

__attribute__((used)) static struct user *
user(uid_t uid)
{
	struct user *usr;
	int i;
	struct passwd *pwd;

	while (1) {
		for (usr = users + (uid&(nusers - 1)), i = nusers; --i >= 0;
		    usr--) {
			if (!usr->name) {
				usr->uid = uid;

				if (!(pwd = getpwuid(uid))) {
					if ((usr->name = (char *)malloc(7)))
						sprintf(usr->name,"#%d",uid);
				} else {
					if ((usr->name = (char *)
					    malloc(strlen(pwd->pw_name) + 1)))
						strcpy(usr->name,pwd->pw_name);
				}
				if (!usr->name)
					errx(1, "allocate users");

				return usr;

			} else if (usr->uid == uid)
				return usr;

			if (usr <= users)
				usr = users + nusers;
		}
		usrrehash();
	}
}
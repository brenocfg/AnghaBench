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
struct user {int uid; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int nusers ; 
 struct user* users ; 

__attribute__((used)) static void
usrrehash(void)
{
	int i;
	struct user *usr, *usrn;
	struct user *svusr;

	svusr = users;
	nusers <<= 1;
	if (!(users = (struct user *)calloc(nusers,sizeof(struct user))))
		errx(1, "allocate users");
	for (usr = svusr, i = nusers >> 1; --i >= 0; usr++) {
		for (usrn = users + (usr->uid&(nusers - 1)); usrn->name;
		    usrn--) {
			if (usrn <= users)
				usrn = users + nusers;
		}
		*usrn = *usr;
	}
}
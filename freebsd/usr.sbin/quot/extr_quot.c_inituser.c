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
struct user {scalar_t__ count; scalar_t__ spc90; scalar_t__ spc60; scalar_t__ spc30; scalar_t__ space; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int nusers ; 
 struct user* users ; 

__attribute__((used)) static void
inituser(void)
{
	int i;
	struct user *usr;

	if (!nusers) {
		nusers = 8;
		if (!(users =
		    (struct user *)calloc(nusers,sizeof(struct user))))
			errx(1, "allocate users");
	} else {
		for (usr = users, i = nusers; --i >= 0; usr++) {
			usr->space = usr->spc30 = usr->spc60 = usr->spc90 = 0;
			usr->count = 0;
		}
	}
}
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
struct utmpx {int dummy; } ;
struct futx {int fu_type; int /*<<< orphan*/  fu_user; } ;

/* Variables and functions */
#define  USER_PROCESS 128 
 struct utmpx* futx_to_utx (struct futx*) ; 
 scalar_t__ getfutxent (struct futx*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

struct utmpx *
getutxuser(const char *user)
{
	struct futx fu;

	for (;;) {
		if (getfutxent(&fu) != 0)
			return (NULL);

		switch (fu.fu_type) {
		case USER_PROCESS:
			if (strncmp(fu.fu_user, user, sizeof(fu.fu_user)) == 0)
				goto found;
			break;
		}
	}

found:
	return (futx_to_utx(&fu));
}
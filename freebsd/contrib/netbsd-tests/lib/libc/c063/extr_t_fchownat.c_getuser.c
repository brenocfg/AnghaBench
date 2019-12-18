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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  USER ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getuser(uid_t *uid, gid_t *gid)
{
	struct passwd *pw;

	if ((pw = getpwnam(USER)) == NULL)
		return -1;

	*uid = pw->pw_uid;
	*gid = pw->pw_gid;

	return 0;
}
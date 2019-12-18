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
struct passwd {char* pw_name; } ;
struct cpio {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ id_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  cpio_i64toa (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_warnc (scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lookup_uname_helper(struct cpio *cpio, const char **name, id_t id)
{
	struct passwd	*pwent;

	(void)cpio; /* UNUSED */

	errno = 0;
	pwent = getpwuid((uid_t)id);
	if (pwent == NULL) {
		if (errno && errno != ENOENT)
			lafe_warnc(errno, "getpwuid(%s) failed",
			    cpio_i64toa((int64_t)id));
		return 1;
	}

	*name = pwent->pw_name;
	return 0;
}
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
struct group {char* gr_name; } ;
struct cpio {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ id_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  cpio_i64toa (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_warnc (scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lookup_gname_helper(struct cpio *cpio, const char **name, id_t id)
{
	struct group	*grent;

	(void)cpio; /* UNUSED */

	errno = 0;
	grent = getgrgid((gid_t)id);
	if (grent == NULL) {
		if (errno && errno != ENOENT)
			lafe_warnc(errno, "getgrgid(%s) failed",
			    cpio_i64toa((int64_t)id));
		return 1;
	}

	*name = grent->gr_name;
	return 0;
}
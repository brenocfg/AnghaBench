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
typedef  int /*<<< orphan*/  u_char ;
struct direct {scalar_t__ d_ino; int d_reclen; scalar_t__ d_namlen; scalar_t__ d_type; } ;

/* Variables and functions */
 scalar_t__ Bcvt ; 
 int DIRBLKSIZ ; 
 size_t DIRSIZ (int /*<<< orphan*/ ,struct direct*) ; 
 scalar_t__ DT_UNKNOWN ; 
 scalar_t__ NAME_MAX ; 
 scalar_t__ oldinofmt ; 
 int /*<<< orphan*/  putent (struct direct*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  swabst (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
putdir(char *buf, size_t size)
{
	struct direct *dp;
	size_t loc, i;

	for (loc = 0; loc < size; ) {
		dp = (struct direct *)(buf + loc);
		if (Bcvt)
			swabst((u_char *)"ls", (u_char *) dp);
		if (oldinofmt && dp->d_ino != 0) {
#if BYTE_ORDER == BIG_ENDIAN
			if (Bcvt)
				dp->d_namlen = dp->d_type;
#else
			if (!Bcvt && dp->d_namlen == 0)
				dp->d_namlen = dp->d_type;
#endif
			dp->d_type = DT_UNKNOWN;
		}
		i = DIRBLKSIZ - (loc & (DIRBLKSIZ - 1));
		if ((dp->d_reclen & 0x3) != 0 ||
		    dp->d_reclen > i ||
		    dp->d_reclen < DIRSIZ(0, dp)
#if NAME_MAX < 255
		    || dp->d_namlen > NAME_MAX
#endif
		    ) {
			vprintf(stdout, "Mangled directory: ");
			if ((dp->d_reclen & 0x3) != 0)
				vprintf(stdout,
				   "reclen not multiple of 4 ");
			if (dp->d_reclen < DIRSIZ(0, dp))
				vprintf(stdout,
				   "reclen less than DIRSIZ (%u < %zu) ",
				   dp->d_reclen, DIRSIZ(0, dp));
#if NAME_MAX < 255
			if (dp->d_namlen > NAME_MAX)
				vprintf(stdout,
				   "reclen name too big (%u > %u) ",
				   dp->d_namlen, NAME_MAX);
#endif
			vprintf(stdout, "\n");
			loc += i;
			continue;
		}
		loc += dp->d_reclen;
		if (dp->d_ino != 0) {
			putent(dp);
		}
	}
}
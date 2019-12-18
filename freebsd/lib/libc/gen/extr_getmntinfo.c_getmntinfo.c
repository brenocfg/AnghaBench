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
struct statfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRIES ; 
 int MNT_NOWAIT ; 
 int SCALING_FACTOR ; 
 int getfsstat (struct statfs*,long,int) ; 
 struct statfs* reallocf (struct statfs*,long) ; 

int
getmntinfo(struct statfs **mntbufp, int mode)
{
	static struct statfs *mntbuf;
	static int mntsize;
	static long bufsize;
	unsigned tries = 0;

	if (mntsize <= 0 && (mntsize = getfsstat(0, 0, MNT_NOWAIT)) < 0)
		return (0);
	if (bufsize > 0 && (mntsize = getfsstat(mntbuf, bufsize, mode)) < 0)
		return (0);
	while (tries++ < MAX_TRIES && bufsize <= mntsize * sizeof(*mntbuf)) {
		bufsize = (mntsize * SCALING_FACTOR) * sizeof(*mntbuf);
		if ((mntbuf = reallocf(mntbuf, bufsize)) == NULL)
			return (0);
		if ((mntsize = getfsstat(mntbuf, bufsize, mode)) < 0)
			return (0);
	}
	*mntbufp = mntbuf;
	if (mntsize > (bufsize / sizeof(*mntbuf)))
		return (bufsize / sizeof(*mntbuf));
	return (mntsize);
}
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
struct direct {scalar_t__ d_reclen; } ;

/* Variables and functions */
 scalar_t__ DIRBLKSIZ ; 
 scalar_t__ DIRSIZ (int /*<<< orphan*/ ,struct direct*) ; 
 int /*<<< orphan*/  df ; 
 scalar_t__ dirbuf ; 
 int /*<<< orphan*/  dirfile ; 
 scalar_t__ dirloc ; 
 int /*<<< orphan*/  fail_dirtmp (int /*<<< orphan*/ ) ; 
 int fwrite (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,struct direct*,long) ; 
 scalar_t__ prev ; 

__attribute__((used)) static void
putent(struct direct *dp)
{
	dp->d_reclen = DIRSIZ(0, dp);
	if (dirloc + dp->d_reclen > DIRBLKSIZ) {
		((struct direct *)(dirbuf + prev))->d_reclen =
		    DIRBLKSIZ - prev;
		if (fwrite(dirbuf, DIRBLKSIZ, 1, df) != 1)
			fail_dirtmp(dirfile);
		dirloc = 0;
	}
	memmove(dirbuf + dirloc, dp, (long)dp->d_reclen);
	prev = dirloc;
	dirloc += dp->d_reclen;
}
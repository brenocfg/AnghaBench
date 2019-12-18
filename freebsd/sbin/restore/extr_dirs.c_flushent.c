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
 int /*<<< orphan*/  df ; 
 scalar_t__ dirbuf ; 
 int /*<<< orphan*/  dirfile ; 
 scalar_t__ dirloc ; 
 int /*<<< orphan*/  fail_dirtmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ ) ; 
 int fwrite (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ prev ; 
 int /*<<< orphan*/  seekpt ; 

__attribute__((used)) static void
flushent(void)
{
	((struct direct *)(dirbuf + prev))->d_reclen = DIRBLKSIZ - prev;
	if (fwrite(dirbuf, (int)dirloc, 1, df) != 1)
		fail_dirtmp(dirfile);
	seekpt = ftell(df);
	dirloc = 0;
}
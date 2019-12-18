#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct m_ext2fs {int /*<<< orphan*/  e2fs_fsmnt; TYPE_1__* e2fs; } ;
typedef  scalar_t__ daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  e2fs_fpg; } ;

/* Variables and functions */
 int NBBY ; 
 int dtogd (struct m_ext2fs*,scalar_t__) ; 
 scalar_t__ ffs (char) ; 
 int howmany (int /*<<< orphan*/ ,int) ; 
 char* memcchr (char*,int,int) ; 
 int /*<<< orphan*/  panic (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static daddr_t
ext2_mapsearch(struct m_ext2fs *fs, char *bbp, daddr_t bpref)
{
	char *loc;
	int start, len;

	/*
	 * find the fragment by searching through the free block
	 * map for an appropriate bit pattern
	 */
	if (bpref)
		start = dtogd(fs, bpref) / NBBY;
	else
		start = 0;
	len = howmany(fs->e2fs->e2fs_fpg, NBBY) - start;
	loc = memcchr(&bbp[start], 0xff, len);
	if (loc == NULL) {
		len = start + 1;
		start = 0;
		loc = memcchr(&bbp[start], 0xff, len);
		if (loc == NULL) {
			panic("ext2_mapsearch: map corrupted: start=%d, len=%d, fs=%s",
			    start, len, fs->e2fs_fsmnt);
			/* NOTREACHED */
		}
	}
	return ((loc - bbp) * NBBY + ffs(~*loc) - 1);
}
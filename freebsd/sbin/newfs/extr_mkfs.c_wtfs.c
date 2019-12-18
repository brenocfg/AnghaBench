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
typedef  scalar_t__ ufs2_daddr_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 scalar_t__ Nflag ; 
 scalar_t__ bwrite (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  err (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ part_ofs ; 

__attribute__((used)) static void
wtfs(ufs2_daddr_t bno, int size, char *bf)
{
	if (Nflag)
		return;
	if (bwrite(&disk, part_ofs + bno, bf, size) < 0)
		err(36, "wtfs: %d bytes at sector %jd", size, (intmax_t)bno);
}
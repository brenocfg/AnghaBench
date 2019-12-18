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

/* Variables and functions */
 scalar_t__ Eflag ; 
 scalar_t__ Zflag ; 
 int /*<<< orphan*/  blerase (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fsbtodb (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fswritefd ; 
 int /*<<< orphan*/  lfragtosize (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sblock ; 

__attribute__((used)) static void
clear_blocks(ufs2_daddr_t start, ufs2_daddr_t end)
{

	if (debug)
		printf("Zero frags %jd to %jd\n", start, end);
	if (Zflag)
		blzero(fswritefd, fsbtodb(&sblock, start),
		    lfragtosize(&sblock, end - start + 1));
	if (Eflag)
		blerase(fswritefd, fsbtodb(&sblock, start),
		    lfragtosize(&sblock, end - start + 1));
}
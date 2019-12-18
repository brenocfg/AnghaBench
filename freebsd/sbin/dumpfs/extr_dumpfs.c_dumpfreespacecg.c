#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fs_fpg; } ;
struct TYPE_3__ {int d_lcg; } ;

/* Variables and functions */
 int /*<<< orphan*/  acg ; 
 TYPE_2__ afs ; 
 int /*<<< orphan*/  cg_blksfree (int /*<<< orphan*/ *) ; 
 TYPE_1__ disk ; 
 int /*<<< orphan*/  pblklist (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
dumpfreespacecg(int fflag)
{

	pblklist(cg_blksfree(&acg), afs.fs_fpg, disk.d_lcg * afs.fs_fpg,
	    fflag);
}
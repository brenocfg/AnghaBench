#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fid {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fh_fid; } ;
typedef  TYPE_1__ fhandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

uint32_t
nfsrv_hashfh(fhandle_t *fhp)
{
	uint32_t hashval;

	hashval = hash32_buf(&fhp->fh_fid, sizeof(struct fid), 0);
	return (hashval);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cg {int dummy; } ;
struct TYPE_4__ {struct cg* b_cg; } ;
struct bufarea {TYPE_1__ b_un; } ;
struct TYPE_5__ {scalar_t__ fs_cgsize; int /*<<< orphan*/  fs_ncg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CYLGRP ; 
 int /*<<< orphan*/  EEXIT ; 
 struct bufarea* calloc (int /*<<< orphan*/ ,int) ; 
 struct bufarea cgblk ; 
 struct bufarea* cgbufs ; 
 int /*<<< orphan*/  cgtod (TYPE_2__*,int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ flushtries ; 
 int /*<<< orphan*/  getblk (struct bufarea*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  initbarea (struct bufarea*,int /*<<< orphan*/ ) ; 
 struct cg* malloc (unsigned int) ; 
 TYPE_2__ sblock ; 

struct bufarea *
cglookup(int cg)
{
	struct bufarea *cgbp;
	struct cg *cgp;

	if (cgbufs == NULL) {
		cgbufs = calloc(sblock.fs_ncg, sizeof(struct bufarea));
		if (cgbufs == NULL)
			errx(EEXIT, "cannot allocate cylinder group buffers");
	}
	cgbp = &cgbufs[cg];
	if (cgbp->b_un.b_cg != NULL)
		return (cgbp);
	cgp = NULL;
	if (flushtries == 0)
		cgp = malloc((unsigned int)sblock.fs_cgsize);
	if (cgp == NULL) {
		getblk(&cgblk, cgtod(&sblock, cg), sblock.fs_cgsize);
		return (&cgblk);
	}
	cgbp->b_un.b_cg = cgp;
	initbarea(cgbp, BT_CYLGRP);
	getblk(cgbp, cgtod(&sblock, cg), sblock.fs_cgsize);
	return (cgbp);
}
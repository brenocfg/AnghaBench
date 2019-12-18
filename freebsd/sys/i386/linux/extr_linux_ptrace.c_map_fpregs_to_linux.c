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
struct linux_pt_fpreg {int /*<<< orphan*/  st_space; int /*<<< orphan*/  fos; int /*<<< orphan*/  foo; int /*<<< orphan*/  fcs; int /*<<< orphan*/  fip; int /*<<< orphan*/  twd; int /*<<< orphan*/  swd; int /*<<< orphan*/  cwd; } ;
struct fpreg {int /*<<< orphan*/  fpr_acc; int /*<<< orphan*/ * fpr_env; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
map_fpregs_to_linux(struct fpreg *bsd_r, struct linux_pt_fpreg *linux_r)
{
	linux_r->cwd = bsd_r->fpr_env[0];
	linux_r->swd = bsd_r->fpr_env[1];
	linux_r->twd = bsd_r->fpr_env[2];
	linux_r->fip = bsd_r->fpr_env[3];
	linux_r->fcs = bsd_r->fpr_env[4];
	linux_r->foo = bsd_r->fpr_env[5];
	linux_r->fos = bsd_r->fpr_env[6];
	bcopy(bsd_r->fpr_acc, linux_r->st_space, sizeof(linux_r->st_space));
}
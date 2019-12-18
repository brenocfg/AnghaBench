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
struct l_ipc64_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;
struct ipc_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;

/* Variables and functions */

__attribute__((used)) static void
linux_to_bsd_ipc_perm(struct l_ipc64_perm *lpp, struct ipc_perm *bpp)
{

	bpp->key = lpp->key;
	bpp->uid = lpp->uid;
	bpp->gid = lpp->gid;
	bpp->cuid = lpp->cuid;
	bpp->cgid = lpp->cgid;
	bpp->mode = lpp->mode;
	bpp->seq = lpp->seq;
}
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
struct l_ipc64_perm {int mode; int /*<<< orphan*/  seq; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;
struct ipc_perm {int mode; int /*<<< orphan*/  seq; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 

__attribute__((used)) static void
bsd_to_linux_ipc_perm(struct ipc_perm *bpp, struct l_ipc64_perm *lpp)
{

	lpp->key = bpp->key;
	lpp->uid = bpp->uid;
	lpp->gid = bpp->gid;
	lpp->cuid = bpp->cuid;
	lpp->cgid = bpp->cgid;
	lpp->mode = bpp->mode & (S_IRWXU|S_IRWXG|S_IRWXO);
	lpp->seq = bpp->seq;
}
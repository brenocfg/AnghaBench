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
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_uid; } ;
struct fuse_ticket {int /*<<< orphan*/  tk_unique; } ;
struct fuse_in_header {int len; int opcode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  unique; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;

/* Variables and functions */

__attribute__((used)) static inline void
fuse_setup_ihead(struct fuse_in_header *ihead, struct fuse_ticket *ftick,
    uint64_t nid, enum fuse_opcode op, size_t blen, pid_t pid,
    struct ucred *cred)
{
	ihead->len = sizeof(*ihead) + blen;
	ihead->unique = ftick->tk_unique;
	ihead->nodeid = nid;
	ihead->opcode = op;

	ihead->pid = pid;
	ihead->uid = cred->cr_uid;
	ihead->gid = cred->cr_groups[0];
}
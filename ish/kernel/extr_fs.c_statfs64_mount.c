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
struct statfsbuf {int /*<<< orphan*/  flags; int /*<<< orphan*/  frsize; int /*<<< orphan*/  namelen; int /*<<< orphan*/  fsid; int /*<<< orphan*/  ffree; int /*<<< orphan*/  files; int /*<<< orphan*/  bavail; int /*<<< orphan*/  bfree; int /*<<< orphan*/  blocks; int /*<<< orphan*/  bsize; int /*<<< orphan*/  type; } ;
struct statfs64_ {int /*<<< orphan*/  flags; int /*<<< orphan*/  frsize; int /*<<< orphan*/  namelen; int /*<<< orphan*/  fsid; int /*<<< orphan*/  ffree; int /*<<< orphan*/  files; int /*<<< orphan*/  bavail; int /*<<< orphan*/  bfree; int /*<<< orphan*/  blocks; int /*<<< orphan*/  bsize; int /*<<< orphan*/  type; } ;
struct mount {int dummy; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int _EFAULT ; 
 int mount_statfs (struct mount*,struct statfsbuf*) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct statfs64_) ; 

__attribute__((used)) static int_t statfs64_mount(struct mount *mount, addr_t buf_addr) {
    struct statfsbuf buf = {};
    int err = mount_statfs(mount, &buf);
    if (err < 0)
        return err;
    struct statfs64_ out_buf = {
        .type = buf.type,
        .bsize = buf.bsize,
        .blocks = buf.blocks,
        .bfree = buf.bfree,
        .bavail = buf.bavail,
        .files = buf.files,
        .ffree = buf.ffree,
        .fsid = buf.fsid,
        .namelen = buf.namelen,
        .frsize = buf.frsize,
        .flags = buf.flags,
    };
    if (user_put(buf_addr, out_buf))
        return _EFAULT;
    return 0;
}
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
struct fd {int real_fd; } ;
struct attr {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
#define  attr_gid 131 
#define  attr_mode 130 
#define  attr_size 129 
#define  attr_uid 128 
 int errno_map () ; 
 int fchmod (int,int /*<<< orphan*/ ) ; 
 int fchown (int,int /*<<< orphan*/ ,int) ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realfs_fsetattr(struct fd *fd, struct attr attr) {
    int real_fd = fd->real_fd;
    int err;
    switch (attr.type) {
        case attr_uid:
            err = fchown(real_fd, attr.uid, -1);
            break;
        case attr_gid:
            err = fchown(real_fd, attr.gid, -1);
            break;
        case attr_mode:
            err = fchmod(real_fd, attr.mode);
            break;
        case attr_size:
            err = ftruncate(real_fd, attr.size);
            break;
    }
    if (err < 0)
        return errno_map();
    return err;
}
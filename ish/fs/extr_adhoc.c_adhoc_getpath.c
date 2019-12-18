#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ inode; } ;
struct fd {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 

__attribute__((used)) static int adhoc_getpath(struct fd *fd, char *buf) {
    const char *type = "unknown"; // TODO allow this to be customized
    if (fd->stat.inode == 0)
        sprintf(buf, "anon_inode:[%s]", type);
    else
        sprintf(buf, "%s:[%lu]", type, (unsigned long) fd->stat.inode);
    return 0;
}
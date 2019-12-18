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
struct fd {TYPE_1__* mount; int /*<<< orphan*/  real_fd; } ;
struct TYPE_2__ {char* source; } ;

/* Variables and functions */
 scalar_t__ MAX_PATH ; 
 int getpath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 

int realfs_getpath(struct fd *fd, char *buf) {
    int err = getpath(fd->real_fd, buf);
    if (err < 0)
        return err;
    if (strcmp(fd->mount->source, "/") != 0 || strcmp(buf, "/") == 0) {
        size_t source_len = strlen(fd->mount->source);
        memmove(buf, buf + source_len, MAX_PATH - source_len);
    }
    return 0;
}
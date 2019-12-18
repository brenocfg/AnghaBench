#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fd {TYPE_2__* mount; } ;
struct TYPE_4__ {char* point; TYPE_1__* fs; } ;
struct TYPE_3__ {int (* getpath ) (struct fd*,char*) ;} ;

/* Variables and functions */
 scalar_t__ MAX_PATH ; 
 int _ENAMETOOLONG ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int stub1 (struct fd*,char*) ; 

int generic_getpath(struct fd *fd, char *buf) {
    int err = fd->mount->fs->getpath(fd, buf);
    if (err < 0)
        return err;
    if (strlen(buf) + strlen(fd->mount->point) >= MAX_PATH)
        return _ENAMETOOLONG;
    memmove(buf + strlen(fd->mount->point), buf, strlen(buf) + 1);
    strncpy(buf, fd->mount->point, strlen(fd->mount->point));
    if (buf[0] == '\0')
        strcpy(buf, "/");
    return 0;
}
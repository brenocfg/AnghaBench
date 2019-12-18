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
struct fd {int /*<<< orphan*/ * ops; } ;
struct dev_ops {int (* open ) (int,int,struct fd*) ;int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int DEV_BLOCK ; 
 int _ENXIO ; 
 struct dev_ops** block_devs ; 
 struct dev_ops** char_devs ; 
 int stub1 (int,int,struct fd*) ; 

int dev_open(int major, int minor, int type, struct fd *fd) {
    struct dev_ops *dev = (type == DEV_BLOCK ? block_devs : char_devs)[major];
    if (dev == NULL)
        return _ENXIO;
    fd->ops = &dev->fd;
    if (!dev->open)
        return 0;
    return dev->open(major, minor, fd);
}
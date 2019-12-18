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
struct fd {int /*<<< orphan*/ * ops; } ;
struct dev_ops {int (* open ) (int,int,struct fd*) ;int /*<<< orphan*/  fd; } ;
struct TYPE_2__ {struct dev_ops** devs; } ;

/* Variables and functions */
 int DEV_CHAR ; 
 int DYN_DEV_MAJOR ; 
 int _ENXIO ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ dyn_info_char ; 
 int stub1 (int,int,struct fd*) ; 

__attribute__((used)) static int dyn_open(int type, int major, int minor, struct fd *fd) {
    assert(type == DEV_CHAR);
    assert(major == DYN_DEV_MAJOR);
    // it's safe to access devs without locking (read-only)
    struct dev_ops *ops = dyn_info_char.devs[minor];
    if (ops == NULL) {
        return _ENXIO;
    }
    fd->ops = &ops->fd;

    // Succeed if there's no open provided by ops
    if (!ops->open)
        return 0;
    return ops->open(major, minor, fd);
}
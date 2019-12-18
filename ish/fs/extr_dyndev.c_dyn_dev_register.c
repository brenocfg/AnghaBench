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
struct dev_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devs_lock; struct dev_ops** devs; } ;

/* Variables and functions */
 int DEV_CHAR ; 
 int DYN_DEV_MAJOR ; 
 int MAX_MINOR ; 
 int _EEXIST ; 
 int _EINVAL ; 
 TYPE_1__ dyn_info_char ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int dyn_dev_register(struct dev_ops *ops, int type, int major, int minor) {
    // Validate arguments
    if (minor < 0 || minor > MAX_MINOR) {
        return _EINVAL;
    }
    if (major != DYN_DEV_MAJOR) {
        return _EINVAL;
    }
    if (ops == NULL) {
        return _EINVAL;
    }
    if (type != DEV_CHAR) {
        return _EINVAL;
    }

    lock(&dyn_info_char.devs_lock);

    // Make sure minor number isn't taken yet
    if (dyn_info_char.devs[minor] != NULL) {
        unlock(&dyn_info_char.devs_lock);
        return _EEXIST;
    }

    dyn_info_char.devs[minor] = ops;
    unlock(&dyn_info_char.devs_lock);

    return 0;
}
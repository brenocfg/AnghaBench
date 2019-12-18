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
struct mount {scalar_t__ root_fd; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_DIRECTORY ; 
 int errno_map () ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int realfs_mount(struct mount *mount) {
    mount->root_fd = open(mount->source, O_DIRECTORY);
    if (mount->root_fd < 0)
        return errno_map();
    return 0;
}
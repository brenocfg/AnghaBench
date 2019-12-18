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
struct fs_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  umask; } ;
typedef  int /*<<< orphan*/  mode_t_ ;
struct TYPE_2__ {struct fs_info* fs; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apply_umask(mode_t_ *mode) {
    struct fs_info *fs = current->fs;
    lock(&fs->lock);
    *mode &= ~fs->umask;
    unlock(&fs->lock);
}
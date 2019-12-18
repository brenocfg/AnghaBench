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
struct fs_info {void* root; void* pwd; int /*<<< orphan*/  umask; } ;

/* Variables and functions */
 void* fd_retain (void*) ; 
 struct fs_info* fs_info_new () ; 

struct fs_info *fs_info_copy(struct fs_info *fs) {
    struct fs_info *new_fs = fs_info_new();
    new_fs->umask = fs->umask;
    new_fs->pwd = fd_retain(fs->pwd);
    new_fs->root = fd_retain(fs->root);
    return new_fs;
}
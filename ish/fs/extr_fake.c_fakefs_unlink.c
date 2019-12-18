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
struct mount {int dummy; } ;
struct TYPE_2__ {int (* unlink ) (struct mount*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int /*<<< orphan*/  path_unlink (struct mount*,char const*) ; 
 TYPE_1__ realfs ; 
 int stub1 (struct mount*,char const*) ; 

__attribute__((used)) static int fakefs_unlink(struct mount *mount, const char *path) {
    db_begin(mount);
    int err = realfs.unlink(mount, path);
    if (err < 0) {
        db_rollback(mount);
        return err;
    }
    path_unlink(mount, path);
    db_commit(mount);
    return 0;
}
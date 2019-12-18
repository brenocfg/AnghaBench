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
struct TYPE_2__ {int (* rename ) (struct mount*,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int /*<<< orphan*/  path_rename (struct mount*,char const*,char const*) ; 
 TYPE_1__ realfs ; 
 int stub1 (struct mount*,char const*,char const*) ; 

__attribute__((used)) static int fakefs_rename(struct mount *mount, const char *src, const char *dst) {
    db_begin(mount);
    path_rename(mount, src, dst);
    int err = realfs.rename(mount, src, dst);
    if (err < 0) {
        db_rollback(mount);
        return err;
    }
    db_commit(mount);
    return 0;
}
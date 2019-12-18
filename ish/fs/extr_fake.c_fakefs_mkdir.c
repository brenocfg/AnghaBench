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
struct mount {int dummy; } ;
struct ish_stat {int mode; scalar_t__ rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int mode_t_ ;
struct TYPE_4__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;
struct TYPE_3__ {int (* mkdir ) (struct mount*,char const*,int) ;} ;

/* Variables and functions */
 int S_IFDIR ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int /*<<< orphan*/  path_create (struct mount*,char const*,struct ish_stat*) ; 
 TYPE_1__ realfs ; 
 int stub1 (struct mount*,char const*,int) ; 

__attribute__((used)) static int fakefs_mkdir(struct mount *mount, const char *path, mode_t_ mode) {
    db_begin(mount);
    int err = realfs.mkdir(mount, path, 0777);
    if (err < 0) {
        db_rollback(mount);
        return err;
    }
    struct ish_stat ishstat;
    ishstat.mode = mode | S_IFDIR;
    ishstat.uid = current->euid;
    ishstat.gid = current->egid;
    ishstat.rdev = 0;
    path_create(mount, path, &ishstat);
    db_commit(mount);
    return 0;
}
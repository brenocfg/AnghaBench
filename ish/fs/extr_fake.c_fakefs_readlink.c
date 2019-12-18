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
struct ish_stat {int /*<<< orphan*/  mode; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ (* readlink ) (struct mount*,char const*,char*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ _EINVAL ; 
 scalar_t__ _ENOENT ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 scalar_t__ file_readlink (struct mount*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  path_read_stat (struct mount*,char const*,struct ish_stat*,int /*<<< orphan*/ *) ; 
 TYPE_1__ realfs ; 
 scalar_t__ stub1 (struct mount*,char const*,char*,size_t) ; 

__attribute__((used)) static ssize_t fakefs_readlink(struct mount *mount, const char *path, char *buf, size_t bufsize) {
    db_begin(mount);
    struct ish_stat ishstat;
    if (!path_read_stat(mount, path, &ishstat, NULL)) {
        db_rollback(mount);
        return _ENOENT;
    }
    if (!S_ISLNK(ishstat.mode)) {
        db_rollback(mount);
        return _EINVAL;
    }

    ssize_t err = realfs.readlink(mount, path, buf, bufsize);
    if (err == _EINVAL)
        err = file_readlink(mount, path, buf, bufsize);
    db_commit(mount);
    return err;
}
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
struct TYPE_2__ {int /*<<< orphan*/  path_create_path; int /*<<< orphan*/  path_create_stat; } ;
struct mount {TYPE_1__ stmt; } ;
struct ish_stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  bind_path (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  db_exec_reset (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ ,int,struct ish_stat*,int,int /*<<< orphan*/ ) ; 

void path_create(struct mount *mount, const char *path, struct ish_stat *stat) {
    // insert into stats (stat) values (?)
    sqlite3_bind_blob(mount->stmt.path_create_stat, 1, stat, sizeof(*stat), SQLITE_TRANSIENT);
    db_exec_reset(mount, mount->stmt.path_create_stat);
    // insert or replace into paths values (?, last_insert_rowid())
    bind_path(mount->stmt.path_create_path, 1, path);
    db_exec_reset(mount, mount->stmt.path_create_path);
}
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
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int SQLITE_ROW ; 
 int /*<<< orphan*/  db_check_error (struct mount*) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool db_exec(struct mount *mount, sqlite3_stmt *stmt) {
    int err = sqlite3_step(stmt);
    db_check_error(mount);
    return err == SQLITE_ROW;
}
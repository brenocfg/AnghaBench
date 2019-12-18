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
struct mount {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  db_check_error (struct mount*) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static sqlite3_stmt *db_prepare(struct mount *mount, const char *stmt) {
    sqlite3_stmt *statement;
    sqlite3_prepare_v2(mount->db, stmt, strlen(stmt) + 1, &statement, NULL);
    db_check_error(mount);
    return statement;
}
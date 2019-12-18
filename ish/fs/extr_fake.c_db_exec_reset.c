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
 int /*<<< orphan*/  db_exec (struct mount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_reset (struct mount*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void db_exec_reset(struct mount *mount, sqlite3_stmt *stmt) {
    db_exec(mount, stmt);
    db_reset(mount, stmt);
}
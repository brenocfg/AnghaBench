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

/* Variables and functions */
#define  SQLITE_DONE 130 
#define  SQLITE_OK 129 
#define  SQLITE_ROW 128 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int sqlite3_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db_check_error(struct mount *mount) {
    int errcode = sqlite3_errcode(mount->db);
    switch (errcode) {
        case SQLITE_OK:
        case SQLITE_ROW:
        case SQLITE_DONE:
            break;

        default:
            die("sqlite error: %s", sqlite3_errmsg(mount->db));
    }
}
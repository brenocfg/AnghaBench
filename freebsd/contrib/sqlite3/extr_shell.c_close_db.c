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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

void close_db(sqlite3 *db){
  int rc = sqlite3_close(db);
  if( rc ){
    utf8_printf(stderr, "Error: sqlite3_close() returns %d: %s\n",
        rc, sqlite3_errmsg(db));
  } 
}
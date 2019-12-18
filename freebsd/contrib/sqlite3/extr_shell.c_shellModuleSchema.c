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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* shellFakeSchema (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shellModuleSchema(
  sqlite3_context *pCtx,
  int nVal,
  sqlite3_value **apVal
){
  const char *zName = (const char*)sqlite3_value_text(apVal[0]);
  char *zFake = shellFakeSchema(sqlite3_context_db_handle(pCtx), 0, zName);
  UNUSED_PARAMETER(nVal);
  if( zFake ){
    sqlite3_result_text(pCtx, sqlite3_mprintf("/* %s */", zFake),
                        -1, sqlite3_free);
    free(zFake);
  }
}
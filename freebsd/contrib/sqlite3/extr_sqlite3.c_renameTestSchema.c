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
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_NAME ; 
 int /*<<< orphan*/  sqlite3NestedParse (int /*<<< orphan*/ *,char*,char const*,char const*,...) ; 

__attribute__((used)) static void renameTestSchema(Parse *pParse, const char *zDb, int bTemp){
  sqlite3NestedParse(pParse, 
      "SELECT 1 "
      "FROM \"%w\".%s "
      "WHERE name NOT LIKE 'sqliteX_%%' ESCAPE 'X'"
      " AND sql NOT LIKE 'create virtual%%'"
      " AND sqlite_rename_test(%Q, sql, type, name, %d)=NULL ",
      zDb, MASTER_NAME, 
      zDb, bTemp
  );

  if( bTemp==0 ){
    sqlite3NestedParse(pParse, 
        "SELECT 1 "
        "FROM temp.%s "
        "WHERE name NOT LIKE 'sqliteX_%%' ESCAPE 'X'"
        " AND sql NOT LIKE 'create virtual%%'"
        " AND sqlite_rename_test(%Q, sql, type, name, 1)=NULL ",
        MASTER_NAME, zDb 
    );
  }
}
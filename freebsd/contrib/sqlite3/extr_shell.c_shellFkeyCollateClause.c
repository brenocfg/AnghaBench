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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_stricmp (char const*,char const*) ; 
 int sqlite3_table_column_metadata (int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shellFkeyCollateClause(
  sqlite3_context *pCtx,
  int nVal,
  sqlite3_value **apVal
){
  sqlite3 *db = sqlite3_context_db_handle(pCtx);
  const char *zParent;
  const char *zParentCol;
  const char *zParentSeq;
  const char *zChild;
  const char *zChildCol;
  const char *zChildSeq = 0;  /* Initialize to avoid false-positive warning */
  int rc;

  assert( nVal==4 );
  zParent = (const char*)sqlite3_value_text(apVal[0]);
  zParentCol = (const char*)sqlite3_value_text(apVal[1]);
  zChild = (const char*)sqlite3_value_text(apVal[2]);
  zChildCol = (const char*)sqlite3_value_text(apVal[3]);

  sqlite3_result_text(pCtx, "", -1, SQLITE_STATIC);
  rc = sqlite3_table_column_metadata(
      db, "main", zParent, zParentCol, 0, &zParentSeq, 0, 0, 0
  );
  if( rc==SQLITE_OK ){
    rc = sqlite3_table_column_metadata(
        db, "main", zChild, zChildCol, 0, &zChildSeq, 0, 0, 0
    );
  }

  if( rc==SQLITE_OK && sqlite3_stricmp(zParentSeq, zChildSeq) ){
    char *z = sqlite3_mprintf(" COLLATE %s", zParentSeq);
    sqlite3_result_text(pCtx, z, -1, SQLITE_TRANSIENT);
    sqlite3_free(z);
  }
}
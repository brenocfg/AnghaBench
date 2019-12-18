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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SQLITE_IOERR ; 
 int /*<<< orphan*/  SQLITE_LIMIT_LENGTH ; 
 int /*<<< orphan*/  SQLITE_TOOBIG ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (void*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int sqlite3_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  sqlite3_result_blob64 (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/  (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void readFileContents(sqlite3_context *ctx, const char *zName){
  FILE *in;
  sqlite3_int64 nIn;
  void *pBuf;
  sqlite3 *db;
  int mxBlob;

  in = fopen(zName, "rb");
  if( in==0 ){
    /* File does not exist or is unreadable. Leave the result set to NULL. */
    return;
  }
  fseek(in, 0, SEEK_END);
  nIn = ftell(in);
  rewind(in);
  db = sqlite3_context_db_handle(ctx);
  mxBlob = sqlite3_limit(db, SQLITE_LIMIT_LENGTH, -1);
  if( nIn>mxBlob ){
    sqlite3_result_error_code(ctx, SQLITE_TOOBIG);
    fclose(in);
    return;
  }
  pBuf = sqlite3_malloc64( nIn ? nIn : 1 );
  if( pBuf==0 ){
    sqlite3_result_error_nomem(ctx);
    fclose(in);
    return;
  }
  if( nIn==(sqlite3_int64)fread(pBuf, 1, (size_t)nIn, in) ){
    sqlite3_result_blob64(ctx, pBuf, nIn, sqlite3_free);
  }else{
    sqlite3_result_error_code(ctx, SQLITE_IOERR);
    sqlite3_free(pBuf);
  }
  fclose(in);
}
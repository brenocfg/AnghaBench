#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_mtime; } ;
struct TYPE_4__ {char* zPath; size_t nBase; TYPE_1__ sStat; } ;
typedef  TYPE_2__ fsdir_cursor ;

/* Variables and functions */
#define  FSDIR_COLUMN_DATA 132 
#define  FSDIR_COLUMN_MODE 131 
#define  FSDIR_COLUMN_MTIME 130 
#define  FSDIR_COLUMN_NAME 129 
#define  FSDIR_COLUMN_PATH 128 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readFileContents (int /*<<< orphan*/ *,char*) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsdirColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  fsdir_cursor *pCur = (fsdir_cursor*)cur;
  switch( i ){
    case FSDIR_COLUMN_NAME: {
      sqlite3_result_text(ctx, &pCur->zPath[pCur->nBase], -1, SQLITE_TRANSIENT);
      break;
    }

    case FSDIR_COLUMN_MODE:
      sqlite3_result_int64(ctx, pCur->sStat.st_mode);
      break;

    case FSDIR_COLUMN_MTIME:
      sqlite3_result_int64(ctx, pCur->sStat.st_mtime);
      break;

    case FSDIR_COLUMN_DATA: {
      mode_t m = pCur->sStat.st_mode;
      if( S_ISDIR(m) ){
        sqlite3_result_null(ctx);
#if !defined(_WIN32) && !defined(WIN32)
      }else if( S_ISLNK(m) ){
        char aStatic[64];
        char *aBuf = aStatic;
        sqlite3_int64 nBuf = 64;
        int n;

        while( 1 ){
          n = readlink(pCur->zPath, aBuf, nBuf);
          if( n<nBuf ) break;
          if( aBuf!=aStatic ) sqlite3_free(aBuf);
          nBuf = nBuf*2;
          aBuf = sqlite3_malloc64(nBuf);
          if( aBuf==0 ){
            sqlite3_result_error_nomem(ctx);
            return SQLITE_NOMEM;
          }
        }

        sqlite3_result_text(ctx, aBuf, n, SQLITE_TRANSIENT);
        if( aBuf!=aStatic ) sqlite3_free(aBuf);
#endif
      }else{
        readFileContents(ctx, pCur->zPath);
      }
    }
    case FSDIR_COLUMN_PATH:
    default: {
      /* The FSDIR_COLUMN_PATH and FSDIR_COLUMN_DIR are input parameters.
      ** always return their values as NULL */
      break;
    }
  }
  return SQLITE_OK;
}
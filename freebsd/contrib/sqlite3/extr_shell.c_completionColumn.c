#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {int szRow; int /*<<< orphan*/  ePhase; int /*<<< orphan*/  zLine; int /*<<< orphan*/  zPrefix; int /*<<< orphan*/  zCurrentRow; } ;
typedef  TYPE_1__ completion_cursor ;

/* Variables and functions */
#define  COMPLETION_COLUMN_CANDIDATE 131 
#define  COMPLETION_COLUMN_PHASE 130 
#define  COMPLETION_COLUMN_PREFIX 129 
#define  COMPLETION_COLUMN_WHOLELINE 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int completionColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  completion_cursor *pCur = (completion_cursor*)cur;
  switch( i ){
    case COMPLETION_COLUMN_CANDIDATE: {
      sqlite3_result_text(ctx, pCur->zCurrentRow, pCur->szRow,SQLITE_TRANSIENT);
      break;
    }
    case COMPLETION_COLUMN_PREFIX: {
      sqlite3_result_text(ctx, pCur->zPrefix, -1, SQLITE_TRANSIENT);
      break;
    }
    case COMPLETION_COLUMN_WHOLELINE: {
      sqlite3_result_text(ctx, pCur->zLine, -1, SQLITE_TRANSIENT);
      break;
    }
    case COMPLETION_COLUMN_PHASE: {
      sqlite3_result_int(ctx, pCur->ePhase);
      break;
    }
  }
  return SQLITE_OK;
}
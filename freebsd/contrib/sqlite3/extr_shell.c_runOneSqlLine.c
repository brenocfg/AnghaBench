#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zPrefix ;
struct TYPE_6__ {int flgProgress; int /*<<< orphan*/  db; int /*<<< orphan*/  out; scalar_t__ nProgress; } ;
typedef  TYPE_1__ ShellState ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_TIMER ; 
 int /*<<< orphan*/  END_TIMER ; 
 int SHELL_PROGRESS_RESET ; 
 int /*<<< orphan*/  SHFLG_Backslash ; 
 int /*<<< orphan*/  SHFLG_CountChanges ; 
 scalar_t__ ShellHasFlag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_db (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_backslashes (char*) ; 
 int shell_exec (TYPE_1__*,char*,char**) ; 
 int /*<<< orphan*/  sqlite3_changes (int /*<<< orphan*/ ) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 
 int /*<<< orphan*/  sqlite3_total_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin_is_interactive ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int runOneSqlLine(ShellState *p, char *zSql, FILE *in, int startline){
  int rc;
  char *zErrMsg = 0;

  open_db(p, 0);
  if( ShellHasFlag(p,SHFLG_Backslash) ) resolve_backslashes(zSql);
  if( p->flgProgress & SHELL_PROGRESS_RESET ) p->nProgress = 0;
  BEGIN_TIMER;
  rc = shell_exec(p, zSql, &zErrMsg);
  END_TIMER;
  if( rc || zErrMsg ){
    char zPrefix[100];
    if( in!=0 || !stdin_is_interactive ){
      sqlite3_snprintf(sizeof(zPrefix), zPrefix,
                       "Error: near line %d:", startline);
    }else{
      sqlite3_snprintf(sizeof(zPrefix), zPrefix, "Error:");
    }
    if( zErrMsg!=0 ){
      utf8_printf(stderr, "%s %s\n", zPrefix, zErrMsg);
      sqlite3_free(zErrMsg);
      zErrMsg = 0;
    }else{
      utf8_printf(stderr, "%s %s\n", zPrefix, sqlite3_errmsg(p->db));
    }
    return 1;
  }else if( ShellHasFlag(p, SHFLG_CountChanges) ){
    raw_printf(p->out, "changes: %3d   total_changes: %d\n",
            sqlite3_changes(p->db), sqlite3_total_changes(p->db));
  }
  return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int lineno; int /*<<< orphan*/  in; scalar_t__ outCount; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 scalar_t__ IsSpace (char) ; 
 int /*<<< orphan*/  SHFLG_Echo ; 
 scalar_t__ ShellHasFlag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _all_whitespace (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bail_on_error ; 
 int /*<<< orphan*/  clearTempFile (TYPE_1__*) ; 
 int do_meta_command (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ line_contains_semicolon (char*,int) ; 
 scalar_t__ line_is_command_terminator (char*) ; 
 scalar_t__ line_is_complete (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* one_input_line (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  output_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* realloc (char*,int) ; 
 scalar_t__ runOneSqlLine (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ seenInterrupt ; 
 int /*<<< orphan*/  shell_out_of_memory () ; 
 scalar_t__ sqlite3_complete (char*) ; 
 scalar_t__ stdin_is_interactive ; 
 int strlen30 (char*) ; 

__attribute__((used)) static int process_input(ShellState *p){
  char *zLine = 0;          /* A single input line */
  char *zSql = 0;           /* Accumulated SQL text */
  int nLine;                /* Length of current line */
  int nSql = 0;             /* Bytes of zSql[] used */
  int nAlloc = 0;           /* Allocated zSql[] space */
  int nSqlPrior = 0;        /* Bytes of zSql[] used by prior line */
  int rc;                   /* Error code */
  int errCnt = 0;           /* Number of errors seen */
  int startline = 0;        /* Line number for start of current input */

  p->lineno = 0;
  while( errCnt==0 || !bail_on_error || (p->in==0 && stdin_is_interactive) ){
    fflush(p->out);
    zLine = one_input_line(p->in, zLine, nSql>0);
    if( zLine==0 ){
      /* End of input */
      if( p->in==0 && stdin_is_interactive ) printf("\n");
      break;
    }
    if( seenInterrupt ){
      if( p->in!=0 ) break;
      seenInterrupt = 0;
    }
    p->lineno++;
    if( nSql==0 && _all_whitespace(zLine) ){
      if( ShellHasFlag(p, SHFLG_Echo) ) printf("%s\n", zLine);
      continue;
    }
    if( zLine && (zLine[0]=='.' || zLine[0]=='#') && nSql==0 ){
      if( ShellHasFlag(p, SHFLG_Echo) ) printf("%s\n", zLine);
      if( zLine[0]=='.' ){
        rc = do_meta_command(zLine, p);
        if( rc==2 ){ /* exit requested */
          break;
        }else if( rc ){
          errCnt++;
        }
      }
      continue;
    }
    if( line_is_command_terminator(zLine) && line_is_complete(zSql, nSql) ){
      memcpy(zLine,";",2);
    }
    nLine = strlen30(zLine);
    if( nSql+nLine+2>=nAlloc ){
      nAlloc = nSql+nLine+100;
      zSql = realloc(zSql, nAlloc);
      if( zSql==0 ) shell_out_of_memory();
    }
    nSqlPrior = nSql;
    if( nSql==0 ){
      int i;
      for(i=0; zLine[i] && IsSpace(zLine[i]); i++){}
      assert( nAlloc>0 && zSql!=0 );
      memcpy(zSql, zLine+i, nLine+1-i);
      startline = p->lineno;
      nSql = nLine-i;
    }else{
      zSql[nSql++] = '\n';
      memcpy(zSql+nSql, zLine, nLine+1);
      nSql += nLine;
    }
    if( nSql && line_contains_semicolon(&zSql[nSqlPrior], nSql-nSqlPrior)
                && sqlite3_complete(zSql) ){
      errCnt += runOneSqlLine(p, zSql, p->in, startline);
      nSql = 0;
      if( p->outCount ){
        output_reset(p);
        p->outCount = 0;
      }else{
        clearTempFile(p);
      }
    }else if( nSql && _all_whitespace(zSql) ){
      if( ShellHasFlag(p, SHFLG_Echo) ) printf("%s\n", zSql);
      nSql = 0;
    }
  }
  if( nSql && !_all_whitespace(zSql) ){
    errCnt += runOneSqlLine(p, zSql, p->in, startline);
  }
  free(zSql);
  free(zLine);
  return errCnt>0;
}
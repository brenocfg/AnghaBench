#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* outfile; int /*<<< orphan*/  out; scalar_t__ doXdgOpen; int /*<<< orphan*/  zTempFile; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  outputModePop (TYPE_1__*) ; 
 int /*<<< orphan*/  output_file_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ system (char*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void output_reset(ShellState *p){
  if( p->outfile[0]=='|' ){
#ifndef SQLITE_OMIT_POPEN
    pclose(p->out);
#endif
  }else{
    output_file_close(p->out);
#ifndef SQLITE_NOHAVE_SYSTEM
    if( p->doXdgOpen ){
      const char *zXdgOpenCmd =
#if defined(_WIN32)
      "start";
#elif defined(__APPLE__)
      "open";
#else
      "xdg-open";
#endif
      char *zCmd;
      zCmd = sqlite3_mprintf("%s %s", zXdgOpenCmd, p->zTempFile);
      if( system(zCmd) ){
        utf8_printf(stderr, "Failed: [%s]\n", zCmd);
      }
      sqlite3_free(zCmd);
      outputModePop(p);
      p->doXdgOpen = 0;
      sqlite3_sleep(100);
    }
#endif /* !defined(SQLITE_NOHAVE_SYSTEM) */
  }
  p->outfile[0] = 0;
  p->out = stdout;
}
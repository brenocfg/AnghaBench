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
struct TYPE_4__ {int lineno; int /*<<< orphan*/ * in; } ;
typedef  TYPE_1__ ShellState ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* find_home_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  process_input (TYPE_1__*) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdin_is_interactive ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void process_sqliterc(
  ShellState *p,                  /* Configuration data */
  const char *sqliterc_override   /* Name of config file. NULL to use default */
){
  char *home_dir = NULL;
  const char *sqliterc = sqliterc_override;
  char *zBuf = 0;
  FILE *inSaved = p->in;
  int savedLineno = p->lineno;

  if (sqliterc == NULL) {
    home_dir = find_home_dir(0);
    if( home_dir==0 ){
      raw_printf(stderr, "-- warning: cannot find home directory;"
                      " cannot read ~/.sqliterc\n");
      return;
    }
    zBuf = sqlite3_mprintf("%s/.sqliterc",home_dir);
    sqliterc = zBuf;
  }
  p->in = fopen(sqliterc,"rb");
  if( p->in ){
    if( stdin_is_interactive ){
      utf8_printf(stderr,"-- Loading resources from %s\n",sqliterc);
    }
    process_input(p);
    fclose(p->in);
  }
  p->in = inSaved;
  p->lineno = savedLineno;
  sqlite3_free(zBuf);
}
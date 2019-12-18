#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int wcnt; char** words; TYPE_1__* dbg; } ;
typedef  TYPE_2__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  debug_command ;
struct TYPE_6__ {char* prvfile; int prvline; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* get_command (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * parse_command (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static debug_command*
get_and_parse_command(mrb_state *mrb, mrdb_state *mrdb)
{
  debug_command *cmd = NULL;
  char *p;
  int i;

  while (!cmd) {
    for (p=NULL; !p || *p=='\0'; ) {
      printf("(%s:%d) ", mrdb->dbg->prvfile, mrdb->dbg->prvline);
      fflush(stdout);
      p = get_command(mrb, mrdb);
    }

    cmd = parse_command(mrb, mrdb, p);
#ifdef _DBG_MRDB_PARSER_
    for (i=0; i<mrdb->wcnt; i++) {
      printf("%d: %s\n", i, mrdb->words[i]);
    }
#endif
    if (!cmd) {
      printf("invalid command (");
      for (i=0; i<mrdb->wcnt; i++) {
        if (i>0) {
          printf(" ");
        }
        printf("%s", mrdb->words[i]);
      }
      puts(")");
    }
  }
  return cmd;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int wcnt; char** words; TYPE_1__* dbg; } ;
typedef  TYPE_2__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  void* mrb_bool ;
struct TYPE_10__ {int line_min; int line_max; int /*<<< orphan*/ * filename; void* parse_error; int /*<<< orphan*/  has_line_max; int /*<<< orphan*/  has_line_min; } ;
typedef  TYPE_3__ listcmd_parser_state ;
struct TYPE_8__ {scalar_t__ prvline; scalar_t__ prvfile; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  parse_filename (int /*<<< orphan*/ *,char**,TYPE_3__*) ; 
 int /*<<< orphan*/  parse_lineno (int /*<<< orphan*/ *,char**,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * replace_ext (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  skip_char (char**,char) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static mrb_bool
parse_listcmd_args(mrb_state *mrb, mrdb_state *mrdb, listcmd_parser_state *st)
{
  char *p;

  switch (mrdb->wcnt) {
  case 2:
    p = mrdb->words[1];

    /* mrdb->words[1] ::= <lineno> | <filename> ':' <lineno> | <filename> */
    if (!parse_lineno(mrb, &p, st)) {
      if (parse_filename(mrb, &p, st)) {
        if (skip_char(&p, ':')) {
          if (!parse_lineno(mrb, &p, st)) {
            st->parse_error = TRUE;
          }
        }
      }
      else {
        st->parse_error = TRUE;
      }
    }
    if (*p != '\0') {
      st->parse_error = TRUE;
    }
    break;
  case 1:
  case 0:
    /* do nothing */
    break;
  default:
    st->parse_error = TRUE;
    printf("too many arguments\n");
    break;
  }

  if (!st->parse_error) {
    if (!st->has_line_min) {
      st->line_min = (!st->filename && mrdb->dbg->prvline > 0) ? mrdb->dbg->prvline : 1;
    }

    if (!st->has_line_max) {
      st->line_max = st->line_min + 9;
    }

    if (st->filename == NULL) {
      if (mrdb->dbg->prvfile && strcmp(mrdb->dbg->prvfile, "-")) {
        st->filename = replace_ext(mrb, mrdb->dbg->prvfile, ".rb");
      }
    }
  }

  if (st->parse_error || st->filename == NULL) {
    return FALSE;
  }

  return TRUE;
}
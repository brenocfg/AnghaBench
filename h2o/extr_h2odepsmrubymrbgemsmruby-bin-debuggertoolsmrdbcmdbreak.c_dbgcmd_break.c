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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dbg; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_debug_context ;
typedef  int mrb_debug_bptype ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 char* BREAK_ERR_MSG_INVALIDARG ; 
 char* BREAK_ERR_MSG_INVALIDFILE ; 
 char* BREAK_ERR_MSG_INVALIDLINENO ; 
 char* BREAK_ERR_MSG_NOOVER ; 
 char* BREAK_ERR_MSG_NUMOVER ; 
 char* BREAK_SET_MSG_CLASS_METHOD ; 
 char* BREAK_SET_MSG_LINE ; 
 char* BREAK_SET_MSG_METHOD ; 
 int /*<<< orphan*/  DBGST_PROMPT ; 
#define  MRB_DEBUG_BPTYPE_LINE 136 
#define  MRB_DEBUG_BPTYPE_METHOD 135 
#define  MRB_DEBUG_BPTYPE_NONE 134 
#define  MRB_DEBUG_BREAK_INVALID_FILE 133 
#define  MRB_DEBUG_BREAK_INVALID_LINENO 132 
#define  MRB_DEBUG_BREAK_NO_OVER 131 
#define  MRB_DEBUG_BREAK_NUM_OVER 130 
#define  MRB_DEBUG_INVALID_ARGUMENT 129 
#define  MRB_DEBUG_NOBUF 128 
 int mrb_debug_set_break_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int mrb_debug_set_break_method (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int parse_breakcommand (TYPE_1__*,char const**,int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 

dbgcmd_state
dbgcmd_break(mrb_state *mrb, mrdb_state *mrdb)
{
  mrb_debug_bptype type;
  mrb_debug_context *dbg = mrdb->dbg;
  const char *file = NULL;
  uint32_t line = 0;
  char *cname = NULL;
  char *method = NULL;
  int32_t ret;

  type = parse_breakcommand(mrdb, &file, &line, &cname, &method);
  switch (type) {
    case MRB_DEBUG_BPTYPE_LINE:
      ret = mrb_debug_set_break_line(mrb, dbg, file, line);
      break;
    case MRB_DEBUG_BPTYPE_METHOD:
      ret = mrb_debug_set_break_method(mrb, dbg, cname, method);
      break;
    case MRB_DEBUG_BPTYPE_NONE:
    default:
      return DBGST_PROMPT;
  }

  if (ret >= 0) {
    if (type == MRB_DEBUG_BPTYPE_LINE) {
      printf(BREAK_SET_MSG_LINE, ret, file, line);
    }
    else if ((type == MRB_DEBUG_BPTYPE_METHOD)&&(cname == NULL)) {
      printf(BREAK_SET_MSG_METHOD, ret, method);
    }
    else {
      printf(BREAK_SET_MSG_CLASS_METHOD, ret, cname, method);
    }
  }
  else {
    switch (ret) {
      case MRB_DEBUG_BREAK_INVALID_LINENO:
        printf(BREAK_ERR_MSG_INVALIDLINENO, line, file);
        break;
      case MRB_DEBUG_BREAK_INVALID_FILE:
        printf(BREAK_ERR_MSG_INVALIDFILE, file);
        break;
      case MRB_DEBUG_BREAK_NUM_OVER:
        puts(BREAK_ERR_MSG_NUMOVER);
        break;
      case MRB_DEBUG_BREAK_NO_OVER:
        puts(BREAK_ERR_MSG_NOOVER);
        break;
      case MRB_DEBUG_INVALID_ARGUMENT:
        puts(BREAK_ERR_MSG_INVALIDARG);
        break;
      case MRB_DEBUG_NOBUF:
        puts("T.B.D.");
        break;
      default:
        break;
    }
  }

  return DBGST_PROMPT;
}
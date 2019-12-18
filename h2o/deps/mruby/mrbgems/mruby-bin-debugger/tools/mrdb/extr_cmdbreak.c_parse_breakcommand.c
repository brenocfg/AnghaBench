#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int wcnt; char** words; TYPE_2__* dbg; } ;
typedef  TYPE_1__ mrdb_state ;
struct TYPE_6__ {TYPE_4__* irep; scalar_t__ pc; } ;
typedef  TYPE_2__ mrb_debug_context ;
typedef  int mrb_debug_bptype ;
struct TYPE_7__ {scalar_t__ iseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_ERR_MSG_BLANK ; 
 char* BREAK_ERR_MSG_INVALIDCLASS ; 
 char* BREAK_ERR_MSG_INVALIDMETHOD ; 
 char* BREAK_ERR_MSG_INVALIDSTR ; 
 int /*<<< orphan*/  BREAK_ERR_MSG_RANGEOVER ; 
 int /*<<< orphan*/  ISLOWER (char) ; 
 int /*<<< orphan*/  ISUPPER (char) ; 
#define  MRB_DEBUG_BPTYPE_LINE 130 
#define  MRB_DEBUG_BPTYPE_METHOD 129 
#define  MRB_DEBUG_BPTYPE_NONE 128 
 int /*<<< orphan*/  STRTOUL (int,char*) ; 
 int check_bptype (char*) ; 
 char* mrb_debug_get_filename (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

mrb_debug_bptype
parse_breakcommand(mrdb_state *mrdb, const char **file, uint32_t *line, char **cname, char **method)
{
  mrb_debug_context *dbg = mrdb->dbg;
  char *args;
  char *body;
  mrb_debug_bptype type;
  uint32_t l;

  if (mrdb->wcnt <= 1) {
    puts(BREAK_ERR_MSG_BLANK);
    return MRB_DEBUG_BPTYPE_NONE;
  }

  args = mrdb->words[1];
  if ((body = strrchr(args, ':')) == NULL) {
    body = args;
    type = check_bptype(body);
  }
  else {
    if (body == args) {
      printf(BREAK_ERR_MSG_INVALIDSTR, args);
      return MRB_DEBUG_BPTYPE_NONE;
    }
    *body = '\0';
    type = check_bptype(++body);
  }

  switch(type) {
    case MRB_DEBUG_BPTYPE_LINE:
      STRTOUL(l, body);
      if (l <= 65535) {
        *line = l;
        *file = (body == args)? mrb_debug_get_filename(dbg->irep, dbg->pc - dbg->irep->iseq): args;
      }
      else {
        puts(BREAK_ERR_MSG_RANGEOVER);
        type = MRB_DEBUG_BPTYPE_NONE;
      }
      break;
    case MRB_DEBUG_BPTYPE_METHOD:
      if (body == args) {
        /* method only */
        if (ISUPPER(*body)||ISLOWER(*body)||(*body == '_')) {
          *method = body;
          *cname = NULL;
        }
        else {
          printf(BREAK_ERR_MSG_INVALIDMETHOD, args);
          type = MRB_DEBUG_BPTYPE_NONE;
        }
      }
      else {
        if (ISUPPER(*args)) {
          switch(*body) {
            case '@': case '$': case '?': case '.': case ',': case ':':
            case ';': case '#': case '\\': case '\'': case '\"':
            printf(BREAK_ERR_MSG_INVALIDMETHOD, body);
            type = MRB_DEBUG_BPTYPE_NONE;
            break;
          default:
            *method = body;
            *cname = args;
            break;
          }
        }
        else {
          printf(BREAK_ERR_MSG_INVALIDCLASS, args);
          type = MRB_DEBUG_BPTYPE_NONE;
        }
      }
      break;
    case MRB_DEBUG_BPTYPE_NONE:
    default:
      break;
  }

  return type;
}
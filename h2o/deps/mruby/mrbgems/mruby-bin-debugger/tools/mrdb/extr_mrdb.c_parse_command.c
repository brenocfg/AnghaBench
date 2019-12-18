#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char** words; int wcnt; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_6__ {size_t len1; size_t len2; scalar_t__ cmd1; scalar_t__ div; scalar_t__ cmd2; } ;
typedef  TYPE_2__ debug_command ;

/* Variables and functions */
 scalar_t__ ISBLANK (char) ; 
 size_t MAX_COMMAND_WORD ; 
 scalar_t__ debug_command_list ; 
 void* pick_out_word (int /*<<< orphan*/ *,char**) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,scalar_t__,size_t) ; 

__attribute__((used)) static debug_command*
parse_command(mrb_state *mrb, mrdb_state *mrdb, char *buf)
{
  debug_command *cmd = NULL;
  char *p = buf;
  size_t wlen;

  /* get word #1 */
  mrdb->words[0] = pick_out_word(mrb, &p);
  if (!mrdb->words[0]) {
    return NULL;
  }
  mrdb->wcnt = 1;
  /* set remain parameter */
  for ( ; *p && ISBLANK(*p); p++) ;
  if (*p) {
    mrdb->words[mrdb->wcnt++] = p;
  }

  /* check word #1 */
  for (cmd=(debug_command*)debug_command_list; cmd->cmd1; cmd++) {
    wlen = strlen(mrdb->words[0]);
    if (wlen >= cmd->len1 &&
        strncmp(mrdb->words[0], cmd->cmd1, wlen) == 0) {
      break;
    }
  }

  if (cmd->cmd2) {
    if (mrdb->wcnt > 1) {
      /* get word #2 */
      mrdb->words[1] = pick_out_word(mrb, &p);
      if (mrdb->words[1]) {
        /* update remain parameter */
        for ( ; *p && ISBLANK(*p); p++) ;
        if (*p) {
          mrdb->words[mrdb->wcnt++] = p;
        }
      }
    }

    /* check word #1,#2 */
    for ( ; cmd->cmd1; cmd++) {
      wlen = strlen(mrdb->words[0]);
      if (wlen < cmd->len1 ||
          strncmp(mrdb->words[0], cmd->cmd1, wlen)) {
        continue;
      }

      if (!cmd->cmd2) break;          /* word #1 only */

      if (mrdb->wcnt == 1) continue;  /* word #2 not specified */

      wlen = strlen(mrdb->words[1]);
      if (wlen >= cmd->len2 &&
          strncmp(mrdb->words[1], cmd->cmd2, wlen) == 0) {
        break;  /* word #1 and #2 */
      }
    }
  }

  /* divide remain parameters */
  if (cmd->cmd1 && cmd->div) {
    p = mrdb->words[--mrdb->wcnt];
    for ( ; mrdb->wcnt<MAX_COMMAND_WORD; mrdb->wcnt++) {
      mrdb->words[mrdb->wcnt] = pick_out_word(mrb, &p);
      if (!mrdb->words[mrdb->wcnt]) {
        break;
      }
    }
  }

  return cmd->cmd1 ? cmd : NULL;
}
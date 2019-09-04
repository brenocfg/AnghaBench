#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_debug_bptype ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_ERR_MSG_BLANK ; 
 char* BREAK_ERR_MSG_INVALIDSTR ; 
 int /*<<< orphan*/  BREAK_ERR_MSG_RANGEOVER ; 
 scalar_t__ ISBLANK (char) ; 
 scalar_t__ ISCNTRL (char) ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 scalar_t__ LINENO_MAX_DIGIT ; 
 int /*<<< orphan*/  MRB_DEBUG_BPTYPE_LINE ; 
 int /*<<< orphan*/  MRB_DEBUG_BPTYPE_METHOD ; 
 int /*<<< orphan*/  MRB_DEBUG_BPTYPE_NONE ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

mrb_debug_bptype
check_bptype(char* args)
{
  char* ps = args;

  if (ISBLANK(*ps)||ISCNTRL(*ps)) {
    puts(BREAK_ERR_MSG_BLANK);
    return MRB_DEBUG_BPTYPE_NONE;
  }

  if (!ISDIGIT(*ps)) {
    return MRB_DEBUG_BPTYPE_METHOD;
  }

  while (!(ISBLANK(*ps)||ISCNTRL(*ps))) {
    if (!ISDIGIT(*ps)) {
      printf(BREAK_ERR_MSG_INVALIDSTR, args);
      return MRB_DEBUG_BPTYPE_NONE;
    }
    ps++;
  }

  if ((*args == '0')||(strlen(args) >= LINENO_MAX_DIGIT)) {
    puts(BREAK_ERR_MSG_RANGEOVER);
    return MRB_DEBUG_BPTYPE_NONE;
  }

  return MRB_DEBUG_BPTYPE_LINE;
}
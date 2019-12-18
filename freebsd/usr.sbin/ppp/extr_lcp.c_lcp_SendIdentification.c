#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_4__ {int /*<<< orphan*/  bundle; } ;
struct TYPE_3__ {char* ident; } ;
struct lcp {char* want_magic; TYPE_2__ fsm; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_IDENT ; 
 int /*<<< orphan*/  DEF_MRU ; 
 int /*<<< orphan*/  LogLCP ; 
 int /*<<< orphan*/  MB_LCPOUT ; 
 int /*<<< orphan*/  command_Expand (char**,int,char const**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_Free (int,char**) ; 
 int /*<<< orphan*/  fsm_Output (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  ua_htonl (char**,char*) ; 

int
lcp_SendIdentification(struct lcp *lcp)
{
  static u_char id;		/* Use a private id */
  u_char msg[DEF_MRU - 3];
  const char *argv[2];
  char *exp[2];

  if (*lcp->cfg.ident == '\0')
    return 0;

  argv[0] = lcp->cfg.ident;
  argv[1] = NULL;

  command_Expand(exp, 1, argv, lcp->fsm.bundle, 1, getpid());

  ua_htonl(&lcp->want_magic, msg);
  strncpy(msg + 4, exp[0], sizeof msg - 5);
  msg[sizeof msg - 1] = '\0';

  fsm_Output(&lcp->fsm, CODE_IDENT, id++, msg, 4 + strlen(msg + 4), MB_LCPOUT);
  log_Printf(LogLCP, " MAGICNUM %08x\n", lcp->want_magic);
  log_Printf(LogLCP, " TEXT %s\n", msg + 4);

  command_Free(1, exp);
  return 1;
}
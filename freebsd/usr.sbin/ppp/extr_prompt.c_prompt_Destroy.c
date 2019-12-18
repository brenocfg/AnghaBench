#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  from; } ;
struct prompt {scalar_t__ Term; scalar_t__ fd_in; scalar_t__ fd_out; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (struct prompt*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_UnRegisterPrompt (struct prompt*) ; 
 int /*<<< orphan*/  prompt_TtyOldMode (struct prompt*) ; 
 scalar_t__ stdout ; 

void
prompt_Destroy(struct prompt *p, int verbose)
{
  if (p) {
    if (p->Term != stdout) {
      fclose(p->Term);
      close(p->fd_in);
      if (p->fd_out != p->fd_in)
        close(p->fd_out);
      if (verbose)
        log_Printf(LogPHASE, "%s: Client connection dropped.\n", p->src.from);
    } else
      prompt_TtyOldMode(p);

    log_UnRegisterPrompt(p);
    free(p);
  }
}
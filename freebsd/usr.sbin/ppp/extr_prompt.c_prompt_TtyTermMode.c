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
struct prompt {scalar_t__ Term; struct datalink* TermMode; int /*<<< orphan*/  fd_in; int /*<<< orphan*/  comtio; } ;
struct datalink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
prompt_TtyTermMode(struct prompt *p, struct datalink *dl)
{
  int stat;

  if (p->Term == stdout)
    tcsetattr(p->fd_in, TCSADRAIN, &p->comtio);

  stat = fcntl(p->fd_in, F_GETFL, 0);
  if (stat > 0) {
    stat &= ~O_NONBLOCK;
    fcntl(p->fd_in, F_SETFL, stat);
  }
  p->TermMode = dl;
}
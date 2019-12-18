#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ c_status; int /*<<< orphan*/ * c_ssh; scalar_t__ c_keytype; int /*<<< orphan*/ * c_data; int /*<<< orphan*/ * c_output_name; int /*<<< orphan*/ * c_namebase; } ;

/* Variables and functions */
 scalar_t__ CS_KEYS ; 
 scalar_t__ CS_UNUSED ; 
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_link ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 TYPE_1__* fdcon ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int maxfd ; 
 int /*<<< orphan*/  ncon ; 
 int /*<<< orphan*/  read_wait ; 
 int /*<<< orphan*/  ssh_packet_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tq ; 

__attribute__((used)) static void
confree(int s)
{
	if (s >= maxfd || fdcon[s].c_status == CS_UNUSED)
		fatal("confree: attempt to free bad fdno %d", s);
	free(fdcon[s].c_namebase);
	free(fdcon[s].c_output_name);
	if (fdcon[s].c_status == CS_KEYS)
		free(fdcon[s].c_data);
	fdcon[s].c_status = CS_UNUSED;
	fdcon[s].c_keytype = 0;
	if (fdcon[s].c_ssh) {
		ssh_packet_close(fdcon[s].c_ssh);
		free(fdcon[s].c_ssh);
		fdcon[s].c_ssh = NULL;
	} else
		close(s);
	TAILQ_REMOVE(&tq, &fdcon[s], c_link);
	FD_CLR(s, read_wait);
	ncon--;
}
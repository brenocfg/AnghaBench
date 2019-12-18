#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tsockaddr {int /*<<< orphan*/  sa_family; } ;
struct TYPE_5__ {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct itimerval {TYPE_1__ it_value; TYPE_1__ it_interval; } ;
struct TYPE_7__ {void* id_num; struct tsockaddr addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  CTL_RESPONSE ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  RING_WAIT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int accept (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  announce_invite () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctl_transact (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* current_state ; 
 int /*<<< orphan*/  end_msgs () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  his_machine_addr ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int invitation_waiting ; 
 int /*<<< orphan*/  invitebuf ; 
 scalar_t__ listen (int,int) ; 
 int local_id ; 
 int /*<<< orphan*/  message (char*) ; 
 TYPE_3__ msg ; 
 TYPE_2__ my_addr ; 
 int /*<<< orphan*/  my_machine_addr ; 
 int /*<<< orphan*/  p_error (char*) ; 
 int /*<<< orphan*/  re_invite ; 
 int remote_id ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sockt ; 
 int /*<<< orphan*/  start_msgs () ; 

void
invite_remote(void)
{
	int new_sockt;
	struct itimerval itimer;
	CTL_RESPONSE response;

	itimer.it_value.tv_sec = RING_WAIT;
	itimer.it_value.tv_usec = 0;
	itimer.it_interval = itimer.it_value;
	if (listen(sockt, 5) != 0)
		p_error("Error on attempt to listen for caller");
	/* copy new style sockaddr to old, swap family (short in old) */
	msg.addr = *(struct tsockaddr *)&my_addr;
	msg.addr.sa_family = htons(my_addr.sin_family);
	msg.id_num = htonl(-1);		/* an impossible id_num */
	invitation_waiting = 1;
	announce_invite();
	/*
	 * Shut off the automatic messages for a while,
	 * so we can use the interrupt timer to resend the invitation
	 */
	end_msgs();
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
	message("Waiting for your party to respond");
	signal(SIGALRM, re_invite);
	(void) setjmp(invitebuf);
	while ((new_sockt = accept(sockt, 0, 0)) < 0) {
		if (errno == EINTR)
			continue;
		p_error("Unable to connect with your party");
	}
	close(sockt);
	sockt = new_sockt;

	/*
	 * Have the daemons delete the invitations now that we
	 * have connected.
	 */
	current_state = "Waiting for your party to respond";
	start_msgs();

	msg.id_num = htonl(local_id);
	ctl_transact(my_machine_addr, msg, DELETE, &response);
	msg.id_num = htonl(remote_id);
	ctl_transact(his_machine_addr, msg, DELETE, &response);
	invitation_waiting = 0;
}
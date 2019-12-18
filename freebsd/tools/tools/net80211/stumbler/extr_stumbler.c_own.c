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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {int /*<<< orphan*/  locked; } ;

/* Variables and functions */
 int DLT_IEEE802_11_RADIO ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_input () ; 
 scalar_t__ bpf_s ; 
 int /*<<< orphan*/  chanhop (struct timeval*) ; 
 TYPE_1__ chaninfo ; 
 int /*<<< orphan*/  check_seen (struct timeval*) ; 
 int /*<<< orphan*/  die (int,char*) ; 
 int hopfreq ; 
 int /*<<< orphan*/  open_bpf (char*,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  setup_if (char*) ; 
 int /*<<< orphan*/  user_input () ; 

void own(char* ifname) {
	int rd;
	fd_set fds;
	struct timeval tv;
	int dlt = DLT_IEEE802_11_RADIO;

	hopfreq = 1000;

	setup_if(ifname);
	open_bpf(ifname, dlt);

	while(1) {
		// XXX innefficient all of this...
		if (!chaninfo.locked)
			chanhop(&tv);
		else {
			tv.tv_sec = 1;
			tv.tv_usec = 0;
		}	

		// especially this...
		check_seen(&tv);	

		FD_ZERO(&fds);
		FD_SET(0, &fds);
		FD_SET(bpf_s, &fds);

		rd = select(bpf_s+1, &fds,NULL , NULL, &tv);
		if (rd == -1)
			die(1, "select()");
		if (FD_ISSET(0, &fds))
			user_input();
		if (FD_ISSET(bpf_s, &fds))
			bpf_input();
	}
}
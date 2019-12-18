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
struct timeval {int /*<<< orphan*/  tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_IEEE802_11_RADIO ; 
 int /*<<< orphan*/  PTW_newattackstate () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int open_bpf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  own (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptw ; 
 int /*<<< orphan*/  send_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_chan (int) ; 
 int /*<<< orphan*/  setup_if (char*) ; 
 int /*<<< orphan*/  tx ; 

void start(char *dev) {
	int fd;

	setup_if(dev);

	fd = open_bpf(dev, DLT_IEEE802_11_RADIO);

	ptw = PTW_newattackstate();
	if (!ptw)
		err(1, "PTW_newattackstate()");

	own(fd);

#if 0
	{
		int i;
		struct timeval tv;
		set_chan(11);
		for (i = 0; i < 10; i++) {
			gettimeofday(&tv, NULL);

			send_ack(tx);
//			usleep(500);
			printf("%lu\n", tv.tv_usec);
		}	
	}	
#endif

	close(fd);
}
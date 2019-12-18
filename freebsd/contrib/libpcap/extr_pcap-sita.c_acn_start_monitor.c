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
struct TYPE_3__ {int first_time; } ;
typedef  TYPE_1__ unit_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  find_unit_by_fd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  send_to_fd (int,int,unsigned char*) ; 

__attribute__((used)) static void acn_start_monitor(int fd, int snaplen, int timeout, int promiscuous, int direction) {
	unsigned char	buf[8];
	unit_t			*u;

	//printf("acn_start_monitor()\n");				// fulko
	find_unit_by_fd(fd, NULL, NULL, &u);
	if (u->first_time == 0) {
		buf[0]					= 'M';
		*(uint32_t *)&buf[1]	= htonl(snaplen);
		buf[5]					= timeout;
		buf[6]					= promiscuous;
		buf[7]					= direction;
	//printf("acn_start_monitor() first time\n");				// fulko
		send_to_fd(fd, 8, buf);								/* send the start monitor command with its parameters to the IOP */
		u->first_time = 1;
	}
	//printf("acn_start_monitor() complete\n");				// fulko
}
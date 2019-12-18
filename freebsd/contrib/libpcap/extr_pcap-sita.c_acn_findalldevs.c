#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ find_fd; scalar_t__ len; scalar_t__ ip; } ;
typedef  TYPE_1__ unit_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIND ; 
 int MAX_CHASSIS ; 
 int MAX_GEOSLOT ; 
 int /*<<< orphan*/  close_with_IOP (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_error_response (scalar_t__,char*) ; 
 scalar_t__ max_fs ; 
 scalar_t__ open_with_IOP (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ process_client_data (char*) ; 
 int /*<<< orphan*/  readfds ; 
 int /*<<< orphan*/  send_to_fd (scalar_t__,int,unsigned char*) ; 
 int /*<<< orphan*/  sort_if_table () ; 
 TYPE_1__** units ; 
 int /*<<< orphan*/  wait_for_all_answers () ; 

int acn_findalldevs(char *errbuf) {								/* returns: -1 = error, 0 = OK */
	int		chassis, geoslot;
	unit_t	*u;

	FD_ZERO(&readfds);
	max_fs = 0;
	for (chassis = 0; chassis <= MAX_CHASSIS; chassis++) {
		for (geoslot = 0; geoslot <= MAX_GEOSLOT; geoslot++) {
			u = &units[chassis][geoslot];
			if (u->ip && (open_with_IOP(u, FIND))) {			/* connect to the remote IOP */
				send_to_fd(u->find_fd, 1, (unsigned char *)"\0");
				if (get_error_response(u->find_fd, errbuf))
					close_with_IOP(chassis, geoslot, FIND);
				else {
					if (u->find_fd > max_fs)
						max_fs = u->find_fd;								/* remember the highest number currently in use */
					FD_SET(u->find_fd, &readfds);						/* we are going to want to read this guy's response to */
					u->len = 0;
					send_to_fd(u->find_fd, 1, (unsigned char *)"Q");		/* this interface query request */
				}
			}
		}
	}
	wait_for_all_answers();
	if (process_client_data(errbuf))
		return -1;
	sort_if_table();
	return 0;
}
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
struct dcons_state {int flags; } ;

/* Variables and functions */
 int DCONS_POLL_OFFLINE ; 
 int F_READY ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  dconschat_fetch_header (struct dcons_state*) ; 
 int /*<<< orphan*/  dconschat_proc_dcons (struct dcons_state*) ; 
 int /*<<< orphan*/  dconschat_proc_socket (struct dcons_state*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int poll_hz ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
dconschat_start_session(struct dcons_state *dc)
{
	int counter = 0;
	int retry = 0;
	int retry_unit_init = MAX(1, poll_hz / 10);
	int retry_unit_offline = poll_hz * DCONS_POLL_OFFLINE;
	int retry_unit = retry_unit_init;
	int retry_max = retry_unit_offline / retry_unit;

	while (1) {
		if (((dc->flags & F_READY) == 0) && ++counter > retry_unit) {
			counter = 0;
			retry ++;
			if (retry > retry_max)
				retry_unit = retry_unit_offline;
			if (verbose) {
				printf("%d/%d ", retry, retry_max);
				fflush(stdout);
			}
			dconschat_fetch_header(dc);
		}
		if ((dc->flags & F_READY) != 0) {
			counter = 0;
			retry = 0;
			retry_unit = retry_unit_init;
			dconschat_proc_dcons(dc);
		}
		dconschat_proc_socket(dc);
	}
	return (0);
}
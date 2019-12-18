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
struct iscsi_session_state {int /*<<< orphan*/  iss_connected; } ;
struct iscsi_session_list {unsigned int isl_nentries; struct iscsi_session_state* isl_pstates; } ;
typedef  int /*<<< orphan*/  isl ;

/* Variables and functions */
 scalar_t__ EMSGSIZE ; 
 int /*<<< orphan*/  ISCSISLIST ; 
 scalar_t__ errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct iscsi_session_list*) ; 
 int /*<<< orphan*/  memset (struct iscsi_session_list*,int /*<<< orphan*/ ,int) ; 
 struct iscsi_session_state* realloc (struct iscsi_session_state*,unsigned int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 

__attribute__((used)) static int
kernel_wait(int iscsi_fd, int timeout)
{
	struct iscsi_session_state *states = NULL;
	const struct iscsi_session_state *state;
	struct iscsi_session_list isl;
	unsigned int i, nentries = 1;
	bool all_connected;
	int error;

	for (;;) {
		for (;;) {
			states = realloc(states,
			    nentries * sizeof(struct iscsi_session_state));
			if (states == NULL)
				xo_err(1, "realloc");

			memset(&isl, 0, sizeof(isl));
			isl.isl_nentries = nentries;
			isl.isl_pstates = states;

			error = ioctl(iscsi_fd, ISCSISLIST, &isl);
			if (error != 0 && errno == EMSGSIZE) {
				nentries *= 4;
				continue;
			}
			break;
		}
		if (error != 0) {
			xo_warn("ISCSISLIST");
			return (error);
		}

		all_connected = true;
		for (i = 0; i < isl.isl_nentries; i++) {
			state = &states[i];

			if (!state->iss_connected) {
				all_connected = false;
				break;
			}
		}

		if (all_connected)
			return (0);

		sleep(1);

		if (timeout > 0) {
			timeout--;
			if (timeout == 0)
				return (1);
		}
	}
}
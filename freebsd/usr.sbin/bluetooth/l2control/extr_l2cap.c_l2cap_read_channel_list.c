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
struct ng_btsocket_l2cap_raw_chan_list {int num_channels; TYPE_1__* channels; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  ng_l2cap_node_chan_ep ;
struct TYPE_3__ {int scid; int dcid; int psm; int imtu; int omtu; int /*<<< orphan*/  state; int /*<<< orphan*/  remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERROR ; 
 int NG_L2CAP_MAX_CHAN_NUM ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_L2CAP_NODE_GET_CHAN_LIST ; 
 char* bdaddrpr (int /*<<< orphan*/ *) ; 
 TYPE_1__* calloc (int,int) ; 
 char* ch_state2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_l2cap_raw_chan_list*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_l2cap_raw_chan_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
l2cap_read_channel_list(int s, int argc, char **argv)
{
	static char const * const	state[] = {
		/* NG_L2CAP_CLOSED */			"CLOSED",
		/* NG_L2CAP_W4_L2CAP_CON_RSP */		"W4_L2CAP_CON_RSP",
		/* NG_L2CAP_W4_L2CA_CON_RSP */		"W4_L2CA_CON_RSP",
		/* NG_L2CAP_CONFIG */			"CONFIG",
		/* NG_L2CAP_OPEN */			"OPEN",
		/* NG_L2CAP_W4_L2CAP_DISCON_RSP */	"W4_L2CAP_DISCON_RSP",
		/* NG_L2CAP_W4_L2CA_DISCON_RSP */	"W4_L2CA_DISCON_RSP"
	};
#define ch_state2str(x)	((x) >= SIZE(state)? "UNKNOWN" : state[(x)])

	struct ng_btsocket_l2cap_raw_chan_list	r;
	int					n, error = OK;

	memset(&r, 0, sizeof(r));
	r.num_channels = NG_L2CAP_MAX_CHAN_NUM;
	r.channels = calloc(NG_L2CAP_MAX_CHAN_NUM,
				sizeof(ng_l2cap_node_chan_ep));
	if (r.channels == NULL) {
		errno = ENOMEM;
		return (ERROR);
	}

	if (ioctl(s, SIOC_L2CAP_NODE_GET_CHAN_LIST, &r, sizeof(r)) < 0) {
		error = ERROR;
		goto out;
	}

	fprintf(stdout, "L2CAP channels:\n");
	fprintf(stdout, 
"Remote BD_ADDR     SCID/ DCID   PSM  IMTU/ OMTU State\n");
	for (n = 0; n < r.num_channels; n++) {
		fprintf(stdout,
			"%-17.17s " \
			"%5d/%5d %5d " \
			"%5d/%5d " \
			"%s\n",
			bdaddrpr(&r.channels[n].remote),
			r.channels[n].scid, r.channels[n].dcid,
			r.channels[n].psm, r.channels[n].imtu,
			r.channels[n].omtu,
			ch_state2str(r.channels[n].state));
	}
out:
	free(r.channels);

	return (error);
}
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
struct ng_btsocket_hci_raw_con_list {int num_connections; TYPE_1__* connections; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  ng_hci_node_con_ep ;
struct TYPE_3__ {int con_handle; scalar_t__ link_type; int mode; scalar_t__ role; int pending; int queue_len; int /*<<< orphan*/  state; int /*<<< orphan*/  encryption_mode; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERROR ; 
 scalar_t__ NG_HCI_LINK_ACL ; 
 int NG_HCI_MAX_CON_NUM ; 
 scalar_t__ NG_HCI_ROLE_MASTER ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_CON_LIST ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 char* hci_bdaddr2str (int /*<<< orphan*/ *) ; 
 char* hci_con_state2str (int /*<<< orphan*/ ) ; 
 char* hci_encrypt2str (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_con_list*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_hci_raw_con_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_read_connection_list(int s, int argc, char **argv)
{
	struct ng_btsocket_hci_raw_con_list	r;
	int					n, error = OK;

	memset(&r, 0, sizeof(r));
	r.num_connections = NG_HCI_MAX_CON_NUM;
	r.connections = calloc(NG_HCI_MAX_CON_NUM, sizeof(ng_hci_node_con_ep));
	if (r.connections == NULL) {
		errno = ENOMEM;
		return (ERROR);
	}

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_CON_LIST, &r, sizeof(r)) < 0) {
		error = ERROR;
		goto out;
	}

	fprintf(stdout,
"Remote BD_ADDR    " \
"Handle " \
"Type " \
"Mode " \
"Role " \
"Encrypt " \
"Pending " \
"Queue " \
"State\n");

	for (n = 0; n < r.num_connections; n++) {
		fprintf(stdout,
"%-17.17s " \
"%6d " \
"%4.4s " \
"%4d " \
"%4.4s " \
"%7.7s " \
"%7d " \
"%5d " \
"%s\n",
			hci_bdaddr2str(&r.connections[n].bdaddr),
			r.connections[n].con_handle,
			(r.connections[n].link_type == NG_HCI_LINK_ACL)?
				"ACL" : "SCO",
			r.connections[n].mode,
			(r.connections[n].role == NG_HCI_ROLE_MASTER)?
				"MAST" : "SLAV",
			hci_encrypt2str(r.connections[n].encryption_mode, 1),
			r.connections[n].pending,
			r.connections[n].queue_len,
			hci_con_state2str(r.connections[n].state));
	}
out:
	free(r.connections);

	return (error);
}
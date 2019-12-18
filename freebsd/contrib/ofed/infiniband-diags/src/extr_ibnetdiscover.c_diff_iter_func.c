#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct iter_diff_data {char* fabric1_prefix; int diff_flags; char* fabric2_prefix; int /*<<< orphan*/  (* out_header_detail ) (TYPE_2__*,char*) ;int /*<<< orphan*/  (* out_header ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ;int /*<<< orphan*/  (* out_port ) (TYPE_1__*,int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  fabric2; } ;
struct TYPE_13__ {scalar_t__ remoteport; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_14__ {int numports; scalar_t__ smalid; int /*<<< orphan*/  nodedesc; TYPE_1__** ports; int /*<<< orphan*/  guid; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,TYPE_2__*) ; 
 int DIFF_FLAG_LID ; 
 int DIFF_FLAG_NODE_DESCRIPTION ; 
 int DIFF_FLAG_PORT_CONNECTION ; 
 int /*<<< orphan*/  IB_SMP_DATA_SIZE ; 
 int /*<<< orphan*/  diff_iter_out_header (TYPE_2__*,struct iter_diff_data*,int*) ; 
 int /*<<< orphan*/  diff_ports (TYPE_2__*,TYPE_2__*,int*,struct iter_diff_data*) ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* ibnd_find_node_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,char*) ; 

__attribute__((used)) static void diff_iter_func(ibnd_node_t * fabric1_node, void *iter_user_data)
{
	struct iter_diff_data *data = iter_user_data;
	ibnd_node_t *fabric2_node;
	ibnd_port_t *fabric1_port;
	int p;

	DEBUG("DEBUG: fabric1_node %p\n", fabric1_node);

	fabric2_node = ibnd_find_node_guid(data->fabric2, fabric1_node->guid);
	if (!fabric2_node) {
		(*data->out_header) (fabric1_node, 0, NULL,
				     data->fabric1_prefix,
				     data->fabric1_prefix);
		for (p = 1; p <= fabric1_node->numports; p++) {
			fabric1_port = fabric1_node->ports[p];
			if (fabric1_port && fabric1_port->remoteport)
				(*data->out_port) (fabric1_port, 0,
						   data->fabric1_prefix);
		}
	} else if (data->diff_flags &
		   (DIFF_FLAG_PORT_CONNECTION | DIFF_FLAG_LID
		    | DIFF_FLAG_NODE_DESCRIPTION)) {
		int out_header_flag = 0;

		if ((data->diff_flags & DIFF_FLAG_LID
		     && fabric1_node->smalid != fabric2_node->smalid) ||
		    (data->diff_flags & DIFF_FLAG_NODE_DESCRIPTION
		     && memcmp(fabric1_node->nodedesc, fabric2_node->nodedesc,
			       IB_SMP_DATA_SIZE))) {
			(*data->out_header) (fabric1_node, 0, NULL, NULL,
					     data->fabric1_prefix);
			(*data->out_header_detail) (fabric2_node,
						    data->fabric2_prefix);
			fprintf(f, "\n");
			out_header_flag++;
		}

		if (fabric1_node->numports != fabric2_node->numports) {
			diff_iter_out_header(fabric1_node, data,
					     &out_header_flag);
			fprintf(f, "%snumports = %d\n", data->fabric1_prefix,
				fabric1_node->numports);
			fprintf(f, "%snumports = %d\n", data->fabric2_prefix,
				fabric2_node->numports);
			return;
		}

		if (data->diff_flags & DIFF_FLAG_PORT_CONNECTION
		    || data->diff_flags & DIFF_FLAG_LID)
			diff_ports(fabric1_node, fabric2_node, &out_header_flag,
				   data);
	}
}
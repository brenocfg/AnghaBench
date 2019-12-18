#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct iter_diff_data {int diff_flags; int /*<<< orphan*/  fabric2_prefix; int /*<<< orphan*/  (* out_port ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fabric1_prefix; } ;
struct TYPE_12__ {scalar_t__ guid; scalar_t__ base_lid; TYPE_2__* remoteport; } ;
typedef  TYPE_3__ ibnd_port_t ;
struct TYPE_13__ {int numports; TYPE_3__** ports; } ;
typedef  TYPE_4__ ibnd_node_t ;
struct TYPE_11__ {scalar_t__ guid; scalar_t__ base_lid; TYPE_1__* node; } ;
struct TYPE_10__ {int /*<<< orphan*/  nodedesc; } ;

/* Variables and functions */
 int DIFF_FLAG_LID ; 
 int DIFF_FLAG_NODE_DESCRIPTION ; 
 int DIFF_FLAG_PORT_CONNECTION ; 
 int /*<<< orphan*/  IB_SMP_DATA_SIZE ; 
 int /*<<< orphan*/  diff_iter_out_header (TYPE_4__*,struct iter_diff_data*,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diff_ports(ibnd_node_t * fabric1_node, ibnd_node_t * fabric2_node,
		       int *out_header_flag, struct iter_diff_data *data)
{
	ibnd_port_t *fabric1_port;
	ibnd_port_t *fabric2_port;
	int p;

	for (p = 1; p <= fabric1_node->numports; p++) {
		int fabric1_out = 0, fabric2_out = 0;

		fabric1_port = fabric1_node->ports[p];
		fabric2_port = fabric2_node->ports[p];

		if (data->diff_flags & DIFF_FLAG_PORT_CONNECTION) {
			if ((fabric1_port && !fabric2_port)
			    || ((fabric1_port && fabric2_port)
				&& (fabric1_port->remoteport
				    && !fabric2_port->remoteport)))
				fabric1_out++;
			else if ((!fabric1_port && fabric2_port)
				 || ((fabric1_port && fabric2_port)
				     && (!fabric1_port->remoteport
					 && fabric2_port->remoteport)))
				fabric2_out++;
			else if ((fabric1_port && fabric2_port)
				 && ((fabric1_port->guid != fabric2_port->guid)
				     ||
				     ((fabric1_port->remoteport
				       && fabric2_port->remoteport)
				      && (fabric1_port->remoteport->guid !=
					  fabric2_port->remoteport->guid)))) {
				fabric1_out++;
				fabric2_out++;
			}
		}

		if ((data->diff_flags & DIFF_FLAG_LID)
		    && fabric1_port && fabric2_port
		    && fabric1_port->base_lid != fabric2_port->base_lid) {
			fabric1_out++;
			fabric2_out++;
		}

		if (data->diff_flags & DIFF_FLAG_PORT_CONNECTION
		    && data->diff_flags & DIFF_FLAG_NODE_DESCRIPTION
		    && fabric1_port && fabric2_port
		    && fabric1_port->remoteport && fabric2_port->remoteport
		    && memcmp(fabric1_port->remoteport->node->nodedesc,
			      fabric2_port->remoteport->node->nodedesc,
			      IB_SMP_DATA_SIZE)) {
			fabric1_out++;
			fabric2_out++;
		}

		if (data->diff_flags & DIFF_FLAG_PORT_CONNECTION
		    && data->diff_flags & DIFF_FLAG_NODE_DESCRIPTION
		    && fabric1_port && fabric2_port
		    && fabric1_port->remoteport && fabric2_port->remoteport
		    && memcmp(fabric1_port->remoteport->node->nodedesc,
			      fabric2_port->remoteport->node->nodedesc,
			      IB_SMP_DATA_SIZE)) {
			fabric1_out++;
			fabric2_out++;
		}

		if (data->diff_flags & DIFF_FLAG_PORT_CONNECTION
		    && data->diff_flags & DIFF_FLAG_LID
		    && fabric1_port && fabric2_port
		    && fabric1_port->remoteport && fabric2_port->remoteport
		    && fabric1_port->remoteport->base_lid != fabric2_port->remoteport->base_lid) {
			fabric1_out++;
			fabric2_out++;
		}

		if (fabric1_out) {
			diff_iter_out_header(fabric1_node, data,
					     out_header_flag);
			(*data->out_port) (fabric1_port, 0,
					   data->fabric1_prefix);
		}
		if (fabric2_out) {
			diff_iter_out_header(fabric1_node, data,
					     out_header_flag);
			(*data->out_port) (fabric2_port, 0,
					   data->fabric2_prefix);
		}
	}
}
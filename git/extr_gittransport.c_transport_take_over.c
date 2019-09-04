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
struct transport {int cannot_reuse; int /*<<< orphan*/ * smart_options; int /*<<< orphan*/ * vtable; struct git_transport_data* data; } ;
struct git_transport_data {int /*<<< orphan*/  options; scalar_t__ got_remote_heads; struct child_process* conn; int /*<<< orphan*/ * fd; } ;
struct child_process {int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  taken_over_vtable ; 
 struct git_transport_data* xcalloc (int,int) ; 

void transport_take_over(struct transport *transport,
			 struct child_process *child)
{
	struct git_transport_data *data;

	if (!transport->smart_options)
		BUG("taking over transport requires non-NULL "
		    "smart_options field.");

	data = xcalloc(1, sizeof(*data));
	data->options = *transport->smart_options;
	data->conn = child;
	data->fd[0] = data->conn->out;
	data->fd[1] = data->conn->in;
	data->got_remote_heads = 0;
	transport->data = data;

	transport->vtable = &taken_over_vtable;
	transport->smart_options = &(data->options);

	transport->cannot_reuse = 1;
}
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
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct upload_pack_data {TYPE_1__ shallows; int /*<<< orphan*/  deepen_relative; int /*<<< orphan*/  writer; int /*<<< orphan*/  deepen_not; int /*<<< orphan*/  deepen_since; int /*<<< orphan*/  deepen_rev_list; int /*<<< orphan*/  depth; } ;
struct object_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE_DEPTH ; 
 int /*<<< orphan*/  deepen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct object_array*) ; 
 scalar_t__ is_repository_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_delim (int) ; 
 int /*<<< orphan*/  packet_writer_write (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  send_shallow_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,struct object_array*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void send_shallow_info(struct upload_pack_data *data,
			      struct object_array *want_obj)
{
	/* No shallow info needs to be sent */
	if (!data->depth && !data->deepen_rev_list && !data->shallows.nr &&
	    !is_repository_shallow(the_repository))
		return;

	packet_writer_write(&data->writer, "shallow-info\n");

	if (!send_shallow_list(&data->writer, data->depth,
			       data->deepen_rev_list,
			       data->deepen_since, &data->deepen_not,
			       data->deepen_relative,
			       &data->shallows, want_obj) &&
	    is_repository_shallow(the_repository))
		deepen(&data->writer, INFINITE_DEPTH, data->deepen_relative,
		       &data->shallows, want_obj);

	packet_delim(1);
}
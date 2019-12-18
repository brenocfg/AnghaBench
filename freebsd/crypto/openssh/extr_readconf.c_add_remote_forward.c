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
struct Forward {scalar_t__ allocated_port; int /*<<< orphan*/  handle; int /*<<< orphan*/  connect_path; int /*<<< orphan*/  connect_port; int /*<<< orphan*/  connect_host; int /*<<< orphan*/  listen_path; int /*<<< orphan*/  listen_port; int /*<<< orphan*/  listen_host; } ;
struct TYPE_3__ {int num_remote_forwards; struct Forward* remote_forwards; } ;
typedef  TYPE_1__ Options ;

/* Variables and functions */
 scalar_t__ forward_equals (struct Forward const*,struct Forward*) ; 
 struct Forward* xreallocarray (struct Forward*,int,int) ; 

void
add_remote_forward(Options *options, const struct Forward *newfwd)
{
	struct Forward *fwd;
	int i;

	/* Don't add duplicates */
	for (i = 0; i < options->num_remote_forwards; i++) {
		if (forward_equals(newfwd, options->remote_forwards + i))
			return;
	}
	options->remote_forwards = xreallocarray(options->remote_forwards,
	    options->num_remote_forwards + 1,
	    sizeof(*options->remote_forwards));
	fwd = &options->remote_forwards[options->num_remote_forwards++];

	fwd->listen_host = newfwd->listen_host;
	fwd->listen_port = newfwd->listen_port;
	fwd->listen_path = newfwd->listen_path;
	fwd->connect_host = newfwd->connect_host;
	fwd->connect_port = newfwd->connect_port;
	fwd->connect_path = newfwd->connect_path;
	fwd->handle = newfwd->handle;
	fwd->allocated_port = 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* transport; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_7__ {int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ git_remote_connected (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void git_remote_disconnect(git_remote *remote)
{
	assert(remote);

	if (git_remote_connected(remote))
		remote->transport->close(remote->transport);
}
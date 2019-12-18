#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* transport; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_6__ {int (* is_connected ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int stub1 (TYPE_2__*) ; 

int git_remote_connected(const git_remote *remote)
{
	assert(remote);

	if (!remote->transport || !remote->transport->is_connected)
		return 0;

	/* Ask the transport if it's connected. */
	return remote->transport->is_connected(remote->transport);
}
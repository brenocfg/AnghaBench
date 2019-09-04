#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
typedef  TYPE_1__ transport_local ;
typedef  int /*<<< orphan*/  git_transport ;

/* Variables and functions */

__attribute__((used)) static int local_read_flags(git_transport *transport, int *flags)
{
	transport_local *t = (transport_local *)transport;

	*flags = t->flags;

	return 0;
}
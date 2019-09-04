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
struct TYPE_2__ {int /*<<< orphan*/  cancelled; } ;
typedef  TYPE_1__ transport_local ;
typedef  int /*<<< orphan*/  git_transport ;

/* Variables and functions */
 int /*<<< orphan*/  git_atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void local_cancel(git_transport *transport)
{
	transport_local *t = (transport_local *)transport;

	git_atomic_set(&t->cancelled, 1);
}
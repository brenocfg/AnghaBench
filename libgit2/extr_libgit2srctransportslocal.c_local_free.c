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
struct TYPE_3__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ transport_local ;
typedef  int /*<<< orphan*/  git_transport ;

/* Variables and functions */
 int /*<<< orphan*/  free_heads (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  local_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void local_free(git_transport *transport)
{
	transport_local *t = (transport_local *)transport;

	free_heads(&t->refs);

	/* Close the transport, if it's still open. */
	local_close(transport);

	/* Free the transport */
	git__free(t);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bthid_server_p ;
struct TYPE_4__ {int /*<<< orphan*/  sessions; int /*<<< orphan*/  intr; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  cons; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  session_close (int /*<<< orphan*/ ) ; 

void
server_shutdown(bthid_server_p srv)
{
	assert(srv != NULL);

	close(srv->cons);
	close(srv->ctrl);
	close(srv->intr);

	while (!LIST_EMPTY(&srv->sessions))
		session_close(LIST_FIRST(&srv->sessions));

	memset(srv, 0, sizeof(*srv));
}
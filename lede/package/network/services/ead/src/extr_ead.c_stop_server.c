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
struct ead_instance {scalar_t__ pid; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  free (struct ead_instance*) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stop_server(struct ead_instance *in, bool do_free)
{
	if (in->pid > 0)
		kill(in->pid, SIGKILL);
	in->pid = 0;
	if (do_free) {
		list_del(&in->list);
		free(in);
	}
}
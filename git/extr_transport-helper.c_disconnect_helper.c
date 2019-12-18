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
struct transport {struct helper_data* data; } ;
struct helper_data {TYPE_1__* helper; int /*<<< orphan*/  out; int /*<<< orphan*/  no_disconnect_req; } ;
struct TYPE_3__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int finish_command (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xwrite (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int disconnect_helper(struct transport *transport)
{
	struct helper_data *data = transport->data;
	int res = 0;

	if (data->helper) {
		if (debug)
			fprintf(stderr, "Debug: Disconnecting.\n");
		if (!data->no_disconnect_req) {
			/*
			 * Ignore write errors; there's nothing we can do,
			 * since we're about to close the pipe anyway. And the
			 * most likely error is EPIPE due to the helper dying
			 * to report an error itself.
			 */
			sigchain_push(SIGPIPE, SIG_IGN);
			xwrite(data->helper->in, "\n", 1);
			sigchain_pop(SIGPIPE);
		}
		close(data->helper->in);
		close(data->helper->out);
		fclose(data->out);
		res = finish_command(data->helper);
		FREE_AND_NULL(data->helper);
	}
	return res;
}
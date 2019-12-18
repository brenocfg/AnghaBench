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
struct xs_watch {int dummy; } ;
struct xctrl_shutdown_reason {int /*<<< orphan*/  (* handler ) () ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int nitems (struct xctrl_shutdown_reason*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 struct xctrl_shutdown_reason* xctrl_shutdown_reasons ; 
 int xs_read (int /*<<< orphan*/ ,char*,char*,int*,void**) ; 
 int xs_write (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void
xctrl_on_watch_event(struct xs_watch *watch, const char **vec, unsigned int len)
{
	const struct xctrl_shutdown_reason *reason;
	const struct xctrl_shutdown_reason *last_reason;
	char *result;
	int   error;
	int   result_len;
	
	error = xs_read(XST_NIL, "control", "shutdown",
			&result_len, (void **)&result);
	if (error != 0)
		return;

	/* Acknowledge the request by writing back an empty string. */
	error = xs_write(XST_NIL, "control", "shutdown", "");
	if (error != 0)
		printf("unable to ack shutdown request, proceeding anyway\n");

	reason = xctrl_shutdown_reasons;
	last_reason = reason + nitems(xctrl_shutdown_reasons);
	while (reason < last_reason) {

		if (!strcmp(result, reason->name)) {
			reason->handler();
			break;
		}
		reason++;
	}

	free(result, M_XENSTORE);
}
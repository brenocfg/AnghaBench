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
typedef  int /*<<< orphan*/  uint64_t ;
struct service_connection {int dummy; } ;
struct service {int s_flags; int (* s_limit ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* s_command ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int CASPER_SERVICE_NO_UNIQ_LIMITS ; 
 int EDOOFUS ; 
 int EOPNOTSUPP ; 
 int NV_FLAG_NO_UNIQUE ; 
 int /*<<< orphan*/ * cap_recv_nvlist (int /*<<< orphan*/ ) ; 
 int cap_send_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * nvlist_create (int) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 char* nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_move_descriptor (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * nvlist_take_nvlist (int /*<<< orphan*/ *,char*) ; 
 int service_connection_clone (struct service*,struct service_connection*) ; 
 int /*<<< orphan*/  service_connection_get_chan (struct service_connection*) ; 
 int /*<<< orphan*/ * service_connection_get_limits (struct service_connection*) ; 
 int /*<<< orphan*/  service_connection_remove (struct service*,struct service_connection*) ; 
 int /*<<< orphan*/  service_connection_set_limits (struct service_connection*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
service_message(struct service *service, struct service_connection *sconn)
{
	nvlist_t *nvlin, *nvlout;
	const char *cmd;
	int error, flags;

	flags = 0;
	if ((service->s_flags & CASPER_SERVICE_NO_UNIQ_LIMITS) != 0)
		flags = NV_FLAG_NO_UNIQUE;

	nvlin = cap_recv_nvlist(service_connection_get_chan(sconn));
	if (nvlin == NULL) {
		service_connection_remove(service, sconn);
		return;
	}

	error = EDOOFUS;
	nvlout = nvlist_create(flags);

	cmd = nvlist_get_string(nvlin, "cmd");
	if (strcmp(cmd, "limit_set") == 0) {
		nvlist_t *nvllim;

		nvllim = nvlist_take_nvlist(nvlin, "limits");
		if (service->s_limit == NULL) {
			error = EOPNOTSUPP;
		} else {
			error = service->s_limit(
			    service_connection_get_limits(sconn), nvllim);
		}
		if (error == 0) {
			service_connection_set_limits(sconn, nvllim);
			/* Function consumes nvllim. */
		} else {
			nvlist_destroy(nvllim);
		}
	} else if (strcmp(cmd, "limit_get") == 0) {
		const nvlist_t *nvllim;

		nvllim = service_connection_get_limits(sconn);
		if (nvllim != NULL)
			nvlist_add_nvlist(nvlout, "limits", nvllim);
		else
			nvlist_add_null(nvlout, "limits");
		error = 0;
	} else if (strcmp(cmd, "clone") == 0) {
		int sock;

		sock = service_connection_clone(service, sconn);
		if (sock == -1) {
			error = errno;
		} else {
			nvlist_move_descriptor(nvlout, "sock", sock);
			error = 0;
		}
	} else {
		error = service->s_command(cmd,
		    service_connection_get_limits(sconn), nvlin, nvlout);
	}

	nvlist_destroy(nvlin);
	nvlist_add_number(nvlout, "error", (uint64_t)error);

	if (cap_send_nvlist(service_connection_get_chan(sconn), nvlout) == -1)
		service_connection_remove(service, sconn);

	nvlist_destroy(nvlout);
}
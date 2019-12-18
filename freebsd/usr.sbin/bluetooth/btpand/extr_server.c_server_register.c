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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int security_description; int /*<<< orphan*/  load_factor; int /*<<< orphan*/  psm; } ;
typedef  TYPE_1__ sdp_nap_profile_t ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  control_path ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ l2cap_mode ; 
 int /*<<< orphan*/  l2cap_psm ; 
 int /*<<< orphan*/  local_bdaddr ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sdp_change_service (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sdp_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdp_open_local (int /*<<< orphan*/ ) ; 
 int sdp_register_service (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  server_avail ; 
 scalar_t__ server_handle ; 
 int /*<<< orphan*/ * server_ss ; 
 int /*<<< orphan*/  service_class ; 
 int /*<<< orphan*/  service_name ; 

__attribute__((used)) static void
server_register(void)
{
	sdp_nap_profile_t p;
	int rv;

	if (server_ss == NULL) {
		server_ss = sdp_open_local(control_path);
		if (server_ss == NULL || sdp_error(server_ss) != 0) {
			log_err("failed to contact SDP server");
			return;
		}
	}

	memset(&p, 0, sizeof(p));
	p.psm = l2cap_psm;
	p.load_factor = server_avail;
	p.security_description = (l2cap_mode == 0 ? 0x0000 : 0x0001);

	if (server_handle)
		rv = sdp_change_service(server_ss, server_handle,
		    (uint8_t *)&p, sizeof(p));
	else
		rv = sdp_register_service(server_ss, service_class,
		    &local_bdaddr, (uint8_t *)&p, sizeof(p), &server_handle);

	if (rv != 0) {
		errno = sdp_error(server_ss);
		log_err("%s: %m", service_name);
		exit(EXIT_FAILURE);
	}
}
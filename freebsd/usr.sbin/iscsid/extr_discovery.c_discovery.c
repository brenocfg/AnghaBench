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
struct pdu {int dummy; } ;
struct keys {int /*<<< orphan*/ * keys_values; int /*<<< orphan*/ ** keys_names; } ;
struct TYPE_2__ {int isc_iser; } ;
struct connection {TYPE_1__ conn_conf; } ;

/* Variables and functions */
 int KEYS_MAX ; 
 int /*<<< orphan*/  kernel_add (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_remove (struct connection*) ; 
 int /*<<< orphan*/  keys_add (struct keys*,char*,char*) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 int /*<<< orphan*/  keys_load (struct keys*,struct pdu*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  keys_save (struct keys*,struct pdu*) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 struct pdu* logout_new_request (struct connection*) ; 
 struct pdu* logout_receive (struct connection*) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 struct pdu* text_new_request (struct connection*) ; 
 struct pdu* text_receive (struct connection*) ; 

void
discovery(struct connection *conn)
{
	struct pdu *request, *response;
	struct keys *request_keys, *response_keys;
	int i;

	log_debugx("beginning discovery session");
	request = text_new_request(conn);
	request_keys = keys_new();
	keys_add(request_keys, "SendTargets", "All");
	keys_save(request_keys, request);
	keys_delete(request_keys);
	request_keys = NULL;
	pdu_send(request);
	pdu_delete(request);
	request = NULL;

	log_debugx("waiting for Text Response");
	response = text_receive(conn);
	response_keys = keys_new();
	keys_load(response_keys, response);
	for (i = 0; i < KEYS_MAX; i++) {
		if (response_keys->keys_names[i] == NULL)
			break;

		if (strcmp(response_keys->keys_names[i], "TargetName") != 0)
			continue;

		log_debugx("adding target %s", response_keys->keys_values[i]);
		/*
		 * XXX: Validate the target name?
		 */
		kernel_add(conn, response_keys->keys_values[i]);
	}
	keys_delete(response_keys);
	pdu_delete(response);

	log_debugx("removing temporary discovery session");
	kernel_remove(conn);

#ifdef ICL_KERNEL_PROXY
	if (conn->conn_conf.isc_iser == 1) {
		/*
		 * If we're going through the proxy, the kernel already
		 * sent Logout PDU for us and destroyed the session,
		 * so we can't send anything anymore.
		 */
		log_debugx("discovery session done");
		return;
	}
#endif

	log_debugx("discovery done; logging out");
	request = logout_new_request(conn);
	pdu_send(request);
	pdu_delete(request);
	request = NULL;

	log_debugx("waiting for Logout Response");
	response = logout_receive(conn);
	pdu_delete(response);

	log_debugx("discovery session done");
}
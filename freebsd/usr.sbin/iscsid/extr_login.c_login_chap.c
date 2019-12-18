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
struct TYPE_2__ {char* isc_mutual_user; } ;
struct connection {TYPE_1__ conn_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debugx (char*) ; 
 struct pdu* login_receive (struct connection*) ; 
 int /*<<< orphan*/  login_send_chap_a (struct connection*) ; 
 int /*<<< orphan*/  login_send_chap_r (struct pdu*) ; 
 int /*<<< orphan*/  login_verify_mutual (struct pdu*) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 

__attribute__((used)) static void
login_chap(struct connection *conn)
{
	struct pdu *response;

	log_debugx("beginning CHAP authentication; sending CHAP_A");
	login_send_chap_a(conn);

	log_debugx("waiting for CHAP_A/CHAP_C/CHAP_I");
	response = login_receive(conn);

	log_debugx("sending CHAP_N/CHAP_R");
	login_send_chap_r(response);
	pdu_delete(response);

	/*
	 * XXX: Make sure this is not susceptible to MITM.
	 */

	log_debugx("waiting for CHAP result");
	response = login_receive(conn);
	if (conn->conn_conf.isc_mutual_user[0] != '\0')
		login_verify_mutual(response);
	pdu_delete(response);

	log_debugx("CHAP authentication done");
}
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
struct pdu {scalar_t__ pdu_bhs; } ;
struct iscsi_bhs_login_request {int bhslr_flags; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int BHSLR_FLAGS_TRANSIT ; 
 int /*<<< orphan*/  BHSLR_STAGE_OPERATIONAL_NEGOTIATION ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 int /*<<< orphan*/  login_negotiate (struct connection*,int /*<<< orphan*/ *) ; 
 struct pdu* login_new_response (struct pdu*) ; 
 struct pdu* login_receive (struct connection*,int) ; 
 int /*<<< orphan*/  login_send_error (struct pdu*,int,int) ; 
 int /*<<< orphan*/  login_set_nsg (struct pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 

__attribute__((used)) static void
login_wait_transition(struct connection *conn)
{
	struct pdu *request, *response;
	struct iscsi_bhs_login_request *bhslr;

	log_debugx("waiting for state transition request");
	request = login_receive(conn, false);
	bhslr = (struct iscsi_bhs_login_request *)request->pdu_bhs;
	if ((bhslr->bhslr_flags & BHSLR_FLAGS_TRANSIT) == 0) {
		login_send_error(request, 0x02, 0x00);
		log_errx(1, "got no \"T\" flag after answering AuthMethod");
	}

	log_debugx("got state transition request");
	response = login_new_response(request);
	pdu_delete(request);
	login_set_nsg(response, BHSLR_STAGE_OPERATIONAL_NEGOTIATION);
	pdu_send(response);
	pdu_delete(response);

	login_negotiate(conn, NULL);
}
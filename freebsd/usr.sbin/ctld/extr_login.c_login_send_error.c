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
struct iscsi_bhs_login_response {char bhslr_status_class; char bhslr_status_detail; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debugx (char*,char,char) ; 
 struct pdu* login_new_response (struct pdu*) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 

__attribute__((used)) static void
login_send_error(struct pdu *request, char class, char detail)
{
	struct pdu *response;
	struct iscsi_bhs_login_response *bhslr2;

	log_debugx("sending Login Response PDU with failure class 0x%x/0x%x; "
	    "see next line for reason", class, detail);
	response = login_new_response(request);
	bhslr2 = (struct iscsi_bhs_login_response *)response->pdu_bhs;
	bhslr2->bhslr_status_class = class;
	bhslr2->bhslr_status_detail = detail;

	pdu_send(response);
	pdu_delete(response);
}
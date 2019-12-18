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
struct keys {int dummy; } ;
struct iscsi_bhs_login_response {int bhslr_status_class; int bhslr_status_detail; } ;

/* Variables and functions */
 int /*<<< orphan*/  keys_add (struct keys*,char*,char const*) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  keys_save (struct keys*,struct pdu*) ; 
 int /*<<< orphan*/  login_csg (struct pdu*) ; 
 struct pdu* login_new_response (struct pdu*) ; 
 int /*<<< orphan*/  login_set_csg (struct pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 

__attribute__((used)) static void
login_redirect(struct pdu *request, const char *target_address)
{
	struct pdu *response;
	struct iscsi_bhs_login_response *bhslr2;
	struct keys *response_keys;

	response = login_new_response(request);
	login_set_csg(response, login_csg(request));
	bhslr2 = (struct iscsi_bhs_login_response *)response->pdu_bhs;
	bhslr2->bhslr_status_class = 0x01;
	bhslr2->bhslr_status_detail = 0x01;

	response_keys = keys_new();
	keys_add(response_keys, "TargetAddress", target_address);

	keys_save(response_keys, response);
	pdu_send(response);
	pdu_delete(response);
	keys_delete(response_keys);
}
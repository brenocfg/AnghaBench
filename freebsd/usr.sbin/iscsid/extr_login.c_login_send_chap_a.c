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
struct pdu {int dummy; } ;
struct keys {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSLR_STAGE_SECURITY_NEGOTIATION ; 
 int /*<<< orphan*/  keys_add (struct keys*,char*,char*) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  keys_save (struct keys*,struct pdu*) ; 
 struct pdu* login_new_request (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdu_delete (struct pdu*) ; 
 int /*<<< orphan*/  pdu_send (struct pdu*) ; 

__attribute__((used)) static void
login_send_chap_a(struct connection *conn)
{
	struct pdu *request;
	struct keys *request_keys;

	request = login_new_request(conn, BHSLR_STAGE_SECURITY_NEGOTIATION);
	request_keys = keys_new();
	keys_add(request_keys, "CHAP_A", "5");
	keys_save(request_keys, request);
	keys_delete(request_keys);
	pdu_send(request);
	pdu_delete(request);
}
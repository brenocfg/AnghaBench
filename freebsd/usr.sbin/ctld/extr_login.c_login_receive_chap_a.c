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
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 char* keys_find (struct keys*,char*) ; 
 int /*<<< orphan*/  keys_load (struct keys*,struct pdu*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  log_errx (int,char*,...) ; 
 scalar_t__ login_list_contains (char const*,char*) ; 
 struct pdu* login_receive (struct connection*,int) ; 
 int /*<<< orphan*/  login_send_error (struct pdu*,int,int) ; 

__attribute__((used)) static struct pdu *
login_receive_chap_a(struct connection *conn)
{
	struct pdu *request;
	struct keys *request_keys;
	const char *chap_a;

	request = login_receive(conn, false);
	request_keys = keys_new();
	keys_load(request_keys, request);

	chap_a = keys_find(request_keys, "CHAP_A");
	if (chap_a == NULL) {
		login_send_error(request, 0x02, 0x07);
		log_errx(1, "received CHAP Login PDU without CHAP_A");
	}
	if (login_list_contains(chap_a, "5") == 0) {
		login_send_error(request, 0x02, 0x01);
		log_errx(1, "received CHAP Login PDU with unsupported CHAP_A "
		    "\"%s\"", chap_a);
	}
	keys_delete(request_keys);

	return (request);
}
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
struct sockaddr_hci {int /*<<< orphan*/  hci_node; } ;
typedef  TYPE_1__* link_key_p ;
typedef  int /*<<< orphan*/ * bdaddr_p ;
struct TYPE_3__ {char* name; int /*<<< orphan*/ * pin; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int send_pin_code_reply (int,struct sockaddr_hci*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
process_pin_code_request_event(int sock, struct sockaddr_hci *addr,
		bdaddr_p bdaddr)
{
	link_key_p	key = NULL;

	syslog(LOG_DEBUG, "Got PIN_Code_Request event from '%s', " \
			"remote bdaddr %s", addr->hci_node,
			bt_ntoa(bdaddr, NULL));

	if ((key = get_key(bdaddr, 0)) != NULL) {
		syslog(LOG_DEBUG, "Found matching entry, " \
				"remote bdaddr %s, name '%s', PIN code %s",
				bt_ntoa(&key->bdaddr, NULL),
				(key->name != NULL)? key->name : "No name",
				(key->pin != NULL)? "exists" : "doesn't exist");

		return (send_pin_code_reply(sock, addr, bdaddr, key->pin));
	}

	syslog(LOG_DEBUG, "Could not PIN code for remote bdaddr %s",
			bt_ntoa(bdaddr, NULL));

	return (send_pin_code_reply(sock, addr, bdaddr, NULL));
}
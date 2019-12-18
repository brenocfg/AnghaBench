#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_hci {int /*<<< orphan*/  hci_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_1__ ng_hci_link_key_notification_ep ;
typedef  TYPE_2__* link_key_p ;
struct TYPE_6__ {char* name; int /*<<< orphan*/ * key; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NG_HCI_KEY_SIZE ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_2__* get_key (int /*<<< orphan*/ *,int) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
process_link_key_notification_event(int sock, struct sockaddr_hci *addr,
		ng_hci_link_key_notification_ep *ep)
{
	link_key_p	key = NULL;

	syslog(LOG_DEBUG, "Got Link_Key_Notification event from '%s', " \
			"remote bdaddr %s", addr->hci_node,
			bt_ntoa(&ep->bdaddr, NULL));

	if ((key = get_key(&ep->bdaddr, 1)) == NULL) {
		syslog(LOG_ERR, "Could not find entry for remote bdaddr %s",
				bt_ntoa(&ep->bdaddr, NULL));
		return (-1);
	}

	syslog(LOG_DEBUG, "Updating link key for the entry, " \
			"remote bdaddr %s, name '%s', link key %s",
			bt_ntoa(&key->bdaddr, NULL),
			(key->name != NULL)? key->name : "No name",
			(key->key != NULL)? "exists" : "doesn't exist");

	if (key->key == NULL) {
		key->key = (uint8_t *) malloc(NG_HCI_KEY_SIZE);
		if (key->key == NULL) {
			syslog(LOG_ERR, "Could not allocate link key");
			exit(1);
		}
	}

	memcpy(key->key, &ep->key, NG_HCI_KEY_SIZE);

	return (0);
}
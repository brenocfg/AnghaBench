#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fw_cdev_send_phy_packet {int* data; int /*<<< orphan*/  closure; int /*<<< orphan*/  generation; } ;
union ioctl_arg {struct fw_cdev_send_phy_packet send_phy_packet; } ;
struct TYPE_8__ {int* header; int header_length; int /*<<< orphan*/  callback; int /*<<< orphan*/  generation; int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/  type; int /*<<< orphan*/  closure; } ;
struct outbound_phy_packet_event {TYPE_4__ p; TYPE_2__ phy_packet; struct client* client; } ;
struct fw_card {TYPE_3__* driver; } ;
struct client {TYPE_1__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* send_request ) (struct fw_card*,TYPE_4__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  is_local; struct fw_card* card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FW_CDEV_EVENT_PHY_PACKET_SENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCODE_100 ; 
 int TCODE_LINK_INTERNAL ; 
 int /*<<< orphan*/  client_get (struct client*) ; 
 scalar_t__ is_ping_packet (int*) ; 
 struct outbound_phy_packet_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outbound_phy_packet_callback ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,TYPE_4__*) ; 

__attribute__((used)) static int ioctl_send_phy_packet(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_send_phy_packet *a = &arg->send_phy_packet;
	struct fw_card *card = client->device->card;
	struct outbound_phy_packet_event *e;

	/* Access policy: Allow this ioctl only on local nodes' device files. */
	if (!client->device->is_local)
		return -ENOSYS;

	e = kzalloc(sizeof(*e) + 4, GFP_KERNEL);
	if (e == NULL)
		return -ENOMEM;

	client_get(client);
	e->client		= client;
	e->p.speed		= SCODE_100;
	e->p.generation		= a->generation;
	e->p.header[0]		= TCODE_LINK_INTERNAL << 4;
	e->p.header[1]		= a->data[0];
	e->p.header[2]		= a->data[1];
	e->p.header_length	= 12;
	e->p.callback		= outbound_phy_packet_callback;
	e->phy_packet.closure	= a->closure;
	e->phy_packet.type	= FW_CDEV_EVENT_PHY_PACKET_SENT;
	if (is_ping_packet(a->data))
			e->phy_packet.length = 4;

	card->driver->send_request(card, &e->p);

	return 0;
}
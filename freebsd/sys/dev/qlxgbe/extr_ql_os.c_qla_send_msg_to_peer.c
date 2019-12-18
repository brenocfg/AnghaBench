#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  msg_from_peer; scalar_t__ peer_dev; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 TYPE_1__* device_get_softc (scalar_t__) ; 

__attribute__((used)) static void
qla_send_msg_to_peer(qla_host_t *ha, uint32_t msg_to_peer)
{
	qla_host_t *ha_peer;
	
	if (ha->peer_dev) {
        	if ((ha_peer = device_get_softc(ha->peer_dev)) != NULL) {

			ha_peer->msg_from_peer = msg_to_peer;
		}
	}
}
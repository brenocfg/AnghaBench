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
struct pcap_dbus {int /*<<< orphan*/  conn; } ;
struct TYPE_4__ {struct pcap_dbus* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 

__attribute__((used)) static void
dbus_cleanup(pcap_t *handle)
{
	struct pcap_dbus *handlep = handle->priv;

	dbus_connection_unref(handlep->conn);

	pcap_cleanup_live_common(handle);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pcap_dbus {int /*<<< orphan*/  conn; } ;
struct TYPE_7__ {int /*<<< orphan*/  errbuf; struct pcap_dbus* priv; } ;
typedef  TYPE_1__ pcap_t ;
struct TYPE_8__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  TYPE_2__ DBusError ;

/* Variables and functions */
 TYPE_2__ DBUS_ERROR_INIT ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  dbus_connection_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * dbus_message_demarshal (void const*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dbus_write(pcap_t *handle, const void *buf, size_t size)
{
	/* XXX, not tested */
	struct pcap_dbus *handlep = handle->priv;

	DBusError error = DBUS_ERROR_INIT;
	DBusMessage *msg;

	if (!(msg = dbus_message_demarshal(buf, size, &error))) {
		pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "dbus_message_demarshal() failed: %s", error.message);
		dbus_error_free(&error);
		return -1;
	}

	dbus_connection_send(handlep->conn, msg, NULL);
	dbus_connection_flush(handlep->conn);

	dbus_message_unref(msg);
	return 0;
}
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
typedef  int /*<<< orphan*/  phys_medium ;
typedef  int /*<<< orphan*/  link_state ;
typedef  int /*<<< orphan*/  hardware_status ;
typedef  int bpf_u_int32 ;
typedef  int NDIS_PHYSICAL_MEDIUM ;
typedef  int NDIS_LINK_STATE ;
typedef  int NDIS_HARDWARE_STATUS ;
typedef  int /*<<< orphan*/  ADAPTER ;

/* Variables and functions */
#define  MediaConnectStateConnected 142 
#define  MediaConnectStateDisconnected 141 
 size_t N_GEN_PHYSICAL_MEDIUM_OIDS ; 
#define  NdisHardwareStatusClosing 140 
#define  NdisHardwareStatusInitializing 139 
#define  NdisHardwareStatusNotReady 138 
#define  NdisHardwareStatusReady 137 
#define  NdisHardwareStatusReset 136 
#define  NdisMediaStateConnected 135 
#define  NdisMediaStateDisconnected 134 
#define  NdisPhysicalMediumBluetooth 133 
#define  NdisPhysicalMediumIrda 132 
#define  NdisPhysicalMediumNative802_11 131 
#define  NdisPhysicalMediumUWB 130 
#define  NdisPhysicalMediumWirelessLan 129 
#define  NdisPhysicalMediumWirelessWan 128 
 int OID_GEN_HARDWARE_STATUS ; 
 int OID_GEN_LINK_STATE ; 
 int OID_GEN_MEDIA_CONNECT_STATUS ; 
 int OID_GEN_PHYSICAL_MEDIUM ; 
 int OID_GEN_PHYSICAL_MEDIUM_EX ; 
 int PCAP_IF_CONNECTION_STATUS_CONNECTED ; 
 int PCAP_IF_CONNECTION_STATUS_DISCONNECTED ; 
 int PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE ; 
 int PCAP_IF_LOOPBACK ; 
 int PCAP_IF_RUNNING ; 
 int PCAP_IF_UP ; 
 int PCAP_IF_WIRELESS ; 
 int /*<<< orphan*/  PacketCloseAdapter (int /*<<< orphan*/ *) ; 
 scalar_t__ PacketGetAirPcapHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PacketOpenAdapter (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int oid_get_request (int /*<<< orphan*/ *,int,int*,size_t*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
get_if_flags(const char *name, bpf_u_int32 *flags, char *errbuf)
{
	char *name_copy;
	ADAPTER *adapter;
	int status;
	size_t len;
	NDIS_HARDWARE_STATUS hardware_status;
#ifdef OID_GEN_PHYSICAL_MEDIUM
	NDIS_PHYSICAL_MEDIUM phys_medium;
	bpf_u_int32 gen_physical_medium_oids[] = {
  #ifdef OID_GEN_PHYSICAL_MEDIUM_EX
		OID_GEN_PHYSICAL_MEDIUM_EX,
  #endif
  		OID_GEN_PHYSICAL_MEDIUM
  	};
#define N_GEN_PHYSICAL_MEDIUM_OIDS	(sizeof gen_physical_medium_oids / sizeof gen_physical_medium_oids[0])
	size_t i;
#endif /* OID_GEN_PHYSICAL_MEDIUM */
#ifdef OID_GEN_LINK_STATE
	NDIS_LINK_STATE link_state;
#endif
	int connect_status;

	if (*flags & PCAP_IF_LOOPBACK) {
		/*
		 * Loopback interface, so the connection status doesn't
		 * apply. and it's not wireless (or wired, for that
		 * matter...).  We presume it's up and running.
		 */
		*flags |= PCAP_IF_UP | PCAP_IF_RUNNING | PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE;
		return (0);
	}

	/*
	 * We need to open the adapter to get this information.
	 *
	 * XXX - PacketOpenAdapter() takes a non-const pointer
	 * as an argument, so we make a copy of the argument and
	 * pass that to it.
	 */
	name_copy = strdup(name);
	adapter = PacketOpenAdapter(name_copy);
	free(name_copy);
	if (adapter == NULL) {
		/*
		 * Give up; if they try to open this device, it'll fail.
		 */
		return (0);
	}

#ifdef HAVE_AIRPCAP_API
	/*
	 * Airpcap.sys do not support the below 'OID_GEN_x' values.
	 * Just set these flags (and none of the '*flags' entered with).
	 */
	if (PacketGetAirPcapHandle(adapter)) {
		/*
		 * Must be "up" and "running" if the above if succeeded.
		 */
		*flags = PCAP_IF_UP | PCAP_IF_RUNNING;

		/*
		 * An airpcap device is a wireless device (duh!)
		 */
		*flags |= PCAP_IF_WIRELESS;

		/*
		 * A "network assosiation state" makes no sense for airpcap.
		 */
		*flags |= PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE;
		PacketCloseAdapter(adapter);
		return (0);
	}
#endif

	/*
	 * Get the hardware status, and derive "up" and "running" from
	 * that.
	 */
	len = sizeof (hardware_status);
	status = oid_get_request(adapter, OID_GEN_HARDWARE_STATUS,
	    &hardware_status, &len, errbuf);
	if (status == 0) {
		switch (hardware_status) {

		case NdisHardwareStatusReady:
			/*
			 * "Available and capable of sending and receiving
			 * data over the wire", so up and running.
			 */
			*flags |= PCAP_IF_UP | PCAP_IF_RUNNING;
			break;

		case NdisHardwareStatusInitializing:
		case NdisHardwareStatusReset:
			/*
			 * "Initializing" or "Resetting", so up, but
			 * not running.
			 */
			*flags |= PCAP_IF_UP;
			break;

		case NdisHardwareStatusClosing:
		case NdisHardwareStatusNotReady:
			/*
			 * "Closing" or "Not ready", so neither up nor
			 * running.
			 */
			break;
		}
	} else {
		/*
		 * Can't get the hardware status, so assume both up and
		 * running.
		 */
		*flags |= PCAP_IF_UP | PCAP_IF_RUNNING;
	}

	/*
	 * Get the network type.
	 */
#ifdef OID_GEN_PHYSICAL_MEDIUM
	/*
	 * Try the OIDs we have for this, in order.
	 */
	for (i = 0; i < N_GEN_PHYSICAL_MEDIUM_OIDS; i++) {
		len = sizeof (phys_medium);
		status = oid_get_request(adapter, gen_physical_medium_oids[i],
		    &phys_medium, &len, errbuf);
		if (status == 0) {
			/*
			 * Success.
			 */
			break;
		}
		/*
		 * Failed.  We can't determine whether it failed
		 * because that particular OID isn't supported
		 * or because some other problem occurred, so we
		 * just drive on and try the next OID.
		 */
	}
	if (status == 0) {
		/*
		 * We got the physical medium.
		 */
		switch (phys_medium) {

		case NdisPhysicalMediumWirelessLan:
		case NdisPhysicalMediumWirelessWan:
		case NdisPhysicalMediumNative802_11:
		case NdisPhysicalMediumBluetooth:
		case NdisPhysicalMediumUWB:
		case NdisPhysicalMediumIrda:
			/*
			 * Wireless.
			 */
			*flags |= PCAP_IF_WIRELESS;
			break;

		default:
			/*
			 * Not wireless.
			 */
			break;
		}
	}
#endif

	/*
	 * Get the connection status.
	 */
#ifdef OID_GEN_LINK_STATE
	len = sizeof(link_state);
	status = oid_get_request(adapter, OID_GEN_LINK_STATE, &link_state,
	    &len, errbuf);
	if (status == 0) {
		/*
		 * NOTE: this also gives us the receive and transmit
		 * link state.
		 */
		switch (link_state.MediaConnectState) {

		case MediaConnectStateConnected:
			/*
			 * It's connected.
			 */
			*flags |= PCAP_IF_CONNECTION_STATUS_CONNECTED;
			break;

		case MediaConnectStateDisconnected:
			/*
			 * It's disconnected.
			 */
			*flags |= PCAP_IF_CONNECTION_STATUS_DISCONNECTED;
			break;
		}
	}
#else
	/*
	 * OID_GEN_LINK_STATE isn't supported because it's not in our SDK.
	 */
	status = -1;
#endif
	if (status == -1) {
		/*
		 * OK, OID_GEN_LINK_STATE didn't work, try
		 * OID_GEN_MEDIA_CONNECT_STATUS.
		 */
		status = oid_get_request(adapter, OID_GEN_MEDIA_CONNECT_STATUS,
		    &connect_status, &len, errbuf);
		if (status == 0) {
			switch (connect_status) {

			case NdisMediaStateConnected:
				/*
				 * It's connected.
				 */
				*flags |= PCAP_IF_CONNECTION_STATUS_CONNECTED;
				break;

			case NdisMediaStateDisconnected:
				/*
				 * It's disconnected.
				 */
				*flags |= PCAP_IF_CONNECTION_STATUS_DISCONNECTED;
				break;
			}
		}
	}
	PacketCloseAdapter(adapter);
	return (0);
}
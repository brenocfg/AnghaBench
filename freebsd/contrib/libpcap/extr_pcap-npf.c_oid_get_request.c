#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  size_t ULONG ;
struct TYPE_5__ {size_t Length; int /*<<< orphan*/  Data; int /*<<< orphan*/  Oid; } ;
typedef  TYPE_1__ PACKET_OID_DATA ;
typedef  int /*<<< orphan*/  ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int /*<<< orphan*/  PacketRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcap_win32_err_to_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
oid_get_request(ADAPTER *adapter, bpf_u_int32 oid, void *data, size_t *lenp,
    char *errbuf)
{
	PACKET_OID_DATA *oid_data_arg;

	/*
	 * Allocate a PACKET_OID_DATA structure to hand to PacketRequest().
	 * It should be big enough to hold "*lenp" bytes of data; it
	 * will actually be slightly larger, as PACKET_OID_DATA has a
	 * 1-byte data array at the end, standing in for the variable-length
	 * data that's actually there.
	 */
	oid_data_arg = malloc(sizeof (PACKET_OID_DATA) + *lenp);
	if (oid_data_arg == NULL) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "Couldn't allocate argument buffer for PacketRequest");
		return (PCAP_ERROR);
	}

	/*
	 * No need to copy the data - we're doing a fetch.
	 */
	oid_data_arg->Oid = oid;
	oid_data_arg->Length = (ULONG)(*lenp);	/* XXX - check for ridiculously large value? */
	if (!PacketRequest(adapter, FALSE, oid_data_arg)) {
		char errmsgbuf[PCAP_ERRBUF_SIZE+1];

		pcap_win32_err_to_str(GetLastError(), errmsgbuf);
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "Error calling PacketRequest: %s", errmsgbuf);
		free(oid_data_arg);
		return (-1);
	}

	/*
	 * Get the length actually supplied.
	 */
	*lenp = oid_data_arg->Length;

	/*
	 * Copy back the data we fetched.
	 */
	memcpy(data, oid_data_arg->Data, *lenp);
	free(oid_data_arg);
	return (0);
}
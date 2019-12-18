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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int member_2; scalar_t__ flags; scalar_t__ vlen; int /*<<< orphan*/  value; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ sdp_attr_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOATTR ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/ * NG_HCI_BDADDR_ANY ; 
 int PROTOCOL_DESCRIPTOR_LIST_BUFFER_SIZE ; 
 scalar_t__ PROTOCOL_DESCRIPTOR_LIST_MINIMAL_SIZE ; 
 int /*<<< orphan*/  SDP_ATTR_INVALID ; 
 scalar_t__ SDP_ATTR_OK ; 
 int /*<<< orphan*/  SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST ; 
 scalar_t__ SDP_ATTR_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_DATA_ALT16 ; 
 scalar_t__ SDP_DATA_ALT32 ; 
 scalar_t__ SDP_DATA_ALT8 ; 
#define  SDP_DATA_SEQ16 130 
#define  SDP_DATA_SEQ32 129 
#define  SDP_DATA_SEQ8 128 
 int /*<<< orphan*/  SDP_GET16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_GET32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_GET8 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_channel_lookup_exit (scalar_t__) ; 
 int rfcomm_proto_list_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  sdp_close (void*) ; 
 scalar_t__ sdp_error (void*) ; 
 void* sdp_open (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ sdp_search (void*,int,int /*<<< orphan*/ *,int,scalar_t__*,int,TYPE_1__*) ; 

int
rfcomm_channel_lookup(bdaddr_t const *local, bdaddr_t const *remote,
			int service, int *channel, int *error)
{
	uint8_t		 buffer[PROTOCOL_DESCRIPTOR_LIST_BUFFER_SIZE];
	void		*ss    = NULL;
	uint16_t	 serv  = (uint16_t) service;
	uint32_t	 attr  = SDP_ATTR_RANGE(
					SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST,
					SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST);
	sdp_attr_t	 proto = { SDP_ATTR_INVALID,0,sizeof(buffer),buffer };
	uint32_t	 type, len;

	if (local == NULL)
		local = NG_HCI_BDADDR_ANY;
	if (remote == NULL || channel == NULL)
		rfcomm_channel_lookup_exit(EINVAL);

	if ((ss = sdp_open(local, remote)) == NULL)
		rfcomm_channel_lookup_exit(ENOMEM);
	if (sdp_error(ss) != 0)
		rfcomm_channel_lookup_exit(sdp_error(ss));

	if (sdp_search(ss, 1, &serv, 1, &attr, 1, &proto) != 0)
		rfcomm_channel_lookup_exit(sdp_error(ss));
	if (proto.flags != SDP_ATTR_OK)
		rfcomm_channel_lookup_exit(ENOATTR);

	sdp_close(ss);
	ss = NULL;

	/*
	 * If it is possible for more than one kind of protocol stack to be 
	 * used to gain access to the service, the ProtocolDescriptorList
	 * takes the form of a data element alternative. We always use the
	 * first protocol stack.
	 *
	 * A minimal Protocol Descriptor List for RFCOMM based service would
	 * look like
	 *
	 * seq8 len8			- 2 bytes
	 *	seq8 len8		- 2 bytes
	 *		uuid16 value16	- 3 bytes	L2CAP
	 *	seq8 len8		- 2 bytes
	 *		uuid16 value16	- 3 bytes	RFCOMM
	 *		uint8  value8	- 2 bytes	RFCOMM param #1 
	 *				=========
	 *				 14 bytes
	 *
	 * Lets not count first [seq8 len8] wrapper, so the minimal size of 
	 * the Protocol Descriptor List (the data we are actually interested
	 * in) for RFCOMM based service would be 12 bytes.
	 */

	if (proto.vlen < PROTOCOL_DESCRIPTOR_LIST_MINIMAL_SIZE)
		rfcomm_channel_lookup_exit(EINVAL);

	SDP_GET8(type, proto.value);

	if (type == SDP_DATA_ALT8) {
		SDP_GET8(len, proto.value);
	} else if (type == SDP_DATA_ALT16) {
		SDP_GET16(len, proto.value);
	} else if (type == SDP_DATA_ALT32) {
		SDP_GET32(len, proto.value);
	} else
		len = 0;

	if (len > 0)
		SDP_GET8(type, proto.value);

	switch (type) {
	case SDP_DATA_SEQ8:
		SDP_GET8(len, proto.value);
		break;

	case SDP_DATA_SEQ16:
		SDP_GET16(len, proto.value);
		break;

	case SDP_DATA_SEQ32:
		SDP_GET32(len, proto.value);
		break;

	default:
		rfcomm_channel_lookup_exit(ENOATTR);
		/* NOT REACHED */
	}

	if (len < PROTOCOL_DESCRIPTOR_LIST_MINIMAL_SIZE)
		rfcomm_channel_lookup_exit(EINVAL);

	return (rfcomm_proto_list_parse(proto.value,
					buffer + proto.vlen, channel, error));
}
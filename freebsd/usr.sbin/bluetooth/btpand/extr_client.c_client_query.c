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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ flags; scalar_t__ attr; int vlen; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ sdp_attr_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ SDP_ATTR_INVALID ; 
 scalar_t__ SDP_ATTR_OK ; 
 scalar_t__ SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST ; 
 int /*<<< orphan*/  SDP_ATTR_RANGE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SDP_UUID_PROTOCOL_BNEP ; 
 int /*<<< orphan*/  SDP_UUID_PROTOCOL_L2CAP ; 
 scalar_t__ _sdp_get_seq (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ _sdp_get_uint16 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _sdp_match_uuid16 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_psm ; 
 int /*<<< orphan*/  local_bdaddr ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_bdaddr ; 
 int /*<<< orphan*/  sdp_close (void*) ; 
 int /*<<< orphan*/  sdp_error (void*) ; 
 void* sdp_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sdp_search (void*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  service_class ; 
 int /*<<< orphan*/  service_name ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
client_query(void)
{
	uint8_t buffer[512];
	sdp_attr_t attr;
	uint32_t range;
	void *ss;
	int rv;
	uint8_t *seq0, *seq1;

	attr.flags = SDP_ATTR_INVALID;
	attr.attr = 0;
	attr.vlen = sizeof(buffer);
	attr.value = buffer;

	range = SDP_ATTR_RANGE(SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST,
			       SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST);

	ss = sdp_open(&local_bdaddr, &remote_bdaddr);
	if (ss == NULL || (errno = sdp_error(ss)) != 0) {
		log_err("%s: %m", service_name);
		exit(EXIT_FAILURE);
	}

	log_info("Searching for %s service at %s",
	    service_name, bt_ntoa(&remote_bdaddr, NULL));

	rv = sdp_search(ss, 1, &service_class, 1, &range, 1, &attr);
	if (rv != 0) {
		log_err("%s: %s", service_name, strerror(sdp_error(ss)));
		exit(EXIT_FAILURE);
	}

	sdp_close(ss);

	if (attr.flags != SDP_ATTR_OK
	    || attr.attr != SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST) {
		log_err("%s service not found", service_name);
		exit(EXIT_FAILURE);
	}

	/*
	 * we expect the following protocol descriptor list
	 *
	 *	seq len
	 *	  seq len
	 *	    uuid value == L2CAP
	 *	    uint16 value16 => PSM
	 *	  seq len
	 *	    uuid value == BNEP
	 */
	if (_sdp_get_seq(&attr.value, attr.value + attr.vlen, &seq0)
	    && _sdp_get_seq(&seq0, attr.value, &seq1)
	    && _sdp_match_uuid16(&seq1, seq0, SDP_UUID_PROTOCOL_L2CAP)
	    && _sdp_get_uint16(&seq1, seq0, &l2cap_psm)
	    && _sdp_get_seq(&seq0, attr.value, &seq1)
	    && _sdp_match_uuid16(&seq1, seq0, SDP_UUID_PROTOCOL_BNEP)) {
		log_info("Found PSM %d for service %s", l2cap_psm, service_name);
		return;
	}

	log_err("%s query failed", service_name);
	exit(EXIT_FAILURE);
}
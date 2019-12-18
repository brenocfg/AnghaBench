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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct urndis_softc {int dummy; } ;
struct rndis_query_req {void* rm_devicevchdl; void* rm_infobufoffset; void* rm_infobuflen; void* rm_oid; void* rm_rid; void* rm_len; void* rm_type; } ;
struct rndis_comp_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 scalar_t__ REMOTE_NDIS_QUERY_MSG ; 
 scalar_t__ RNDIS_HEADER_OFFSET ; 
 scalar_t__ RNDIS_STATUS_FAILURE ; 
 scalar_t__ RNDIS_STATUS_SUCCESS ; 
 void* htole32 (scalar_t__) ; 
 int /*<<< orphan*/  le32toh (void*) ; 
 scalar_t__ urndis_ctrl_handle (struct urndis_softc*,struct rndis_comp_hdr*,void const**,scalar_t__*) ; 
 struct rndis_comp_hdr* urndis_ctrl_recv (struct urndis_softc*) ; 
 scalar_t__ urndis_ctrl_send (struct urndis_softc*,struct rndis_query_req*,scalar_t__) ; 

__attribute__((used)) static uint32_t
urndis_ctrl_query(struct urndis_softc *sc, uint32_t oid,
    struct rndis_query_req *msg, uint16_t len, const void **rbuf,
    uint16_t *rbufsz)
{
	struct rndis_comp_hdr *hdr;
	uint32_t datalen, rval;

	msg->rm_type = htole32(REMOTE_NDIS_QUERY_MSG);
	msg->rm_len = htole32(len);
	msg->rm_rid = 0;		/* XXX */
	msg->rm_oid = htole32(oid);
	datalen = len - sizeof(*msg);
	msg->rm_infobuflen = htole32(datalen);
	if (datalen != 0) {
		msg->rm_infobufoffset = htole32(sizeof(*msg) -
		    RNDIS_HEADER_OFFSET);
	} else {
		msg->rm_infobufoffset = 0;
	}
	msg->rm_devicevchdl = 0;

	DPRINTF("type %u len %u rid %u oid 0x%x "
	    "infobuflen %u infobufoffset %u devicevchdl %u\n",
	    le32toh(msg->rm_type),
	    le32toh(msg->rm_len),
	    le32toh(msg->rm_rid),
	    le32toh(msg->rm_oid),
	    le32toh(msg->rm_infobuflen),
	    le32toh(msg->rm_infobufoffset),
	    le32toh(msg->rm_devicevchdl));

	rval = urndis_ctrl_send(sc, msg, len);

	if (rval != RNDIS_STATUS_SUCCESS) {
		DPRINTF("query failed\n");
		return (rval);
	}
	if ((hdr = urndis_ctrl_recv(sc)) == NULL) {
		DPRINTF("unable to get query response\n");
		return (RNDIS_STATUS_FAILURE);
	}
	rval = urndis_ctrl_handle(sc, hdr, rbuf, rbufsz);

	return (rval);
}
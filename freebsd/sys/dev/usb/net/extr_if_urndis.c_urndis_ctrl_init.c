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
struct urndis_softc {int dummy; } ;
struct rndis_init_req {void* rm_max_xfersz; void* rm_ver_minor; void* rm_ver_major; void* rm_rid; void* rm_len; void* rm_type; } ;
struct rndis_comp_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int REMOTE_NDIS_INITIALIZE_MSG ; 
 int RNDIS_RX_MAXLEN ; 
 scalar_t__ RNDIS_STATUS_FAILURE ; 
 scalar_t__ RNDIS_STATUS_SUCCESS ; 
 int RNDIS_VERSION_MAJOR ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  le32toh (void*) ; 
 scalar_t__ urndis_ctrl_handle (struct urndis_softc*,struct rndis_comp_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rndis_comp_hdr* urndis_ctrl_recv (struct urndis_softc*) ; 
 scalar_t__ urndis_ctrl_send (struct urndis_softc*,struct rndis_init_req*,int) ; 

__attribute__((used)) static uint32_t
urndis_ctrl_init(struct urndis_softc *sc)
{
	struct rndis_init_req msg;
	struct rndis_comp_hdr *hdr;
	uint32_t rval;

	msg.rm_type = htole32(REMOTE_NDIS_INITIALIZE_MSG);
	msg.rm_len = htole32(sizeof(msg));
	msg.rm_rid = 0;
	msg.rm_ver_major = htole32(RNDIS_VERSION_MAJOR);
	msg.rm_ver_minor = htole32(1);
	msg.rm_max_xfersz = htole32(RNDIS_RX_MAXLEN);

	DPRINTF("type %u len %u rid %u ver_major %u "
	    "ver_minor %u max_xfersz %u\n",
	    le32toh(msg.rm_type),
	    le32toh(msg.rm_len),
	    le32toh(msg.rm_rid),
	    le32toh(msg.rm_ver_major),
	    le32toh(msg.rm_ver_minor),
	    le32toh(msg.rm_max_xfersz));

	rval = urndis_ctrl_send(sc, &msg, sizeof(msg));

	if (rval != RNDIS_STATUS_SUCCESS) {
		DPRINTF("init failed\n");
		return (rval);
	}
	if ((hdr = urndis_ctrl_recv(sc)) == NULL) {
		DPRINTF("unable to get init response\n");
		return (RNDIS_STATUS_FAILURE);
	}
	rval = urndis_ctrl_handle(sc, hdr, NULL, NULL);

	return (rval);
}
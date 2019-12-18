#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct icl_pdu {scalar_t__ ip_data_len; int /*<<< orphan*/  ip_data_mbuf; TYPE_1__* ip_conn; } ;
typedef  int /*<<< orphan*/  received_digest ;
struct TYPE_2__ {int ic_data_crc32c; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int /*<<< orphan*/  ICL_DEBUG (char*) ; 
 int /*<<< orphan*/  ICL_WARN (char*,scalar_t__,scalar_t__) ; 
 int ISCSI_DATA_DIGEST_SIZE ; 
 scalar_t__ icl_conn_receive_buf (TYPE_1__*,scalar_t__*,int) ; 
 scalar_t__ icl_mbuf_to_crc32c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icl_pdu_check_data_digest(struct icl_pdu *request, size_t *availablep)
{
	uint32_t received_digest, valid_digest;

	if (request->ip_conn->ic_data_crc32c == false)
		return (0);

	if (request->ip_data_len == 0)
		return (0);

	CTASSERT(sizeof(received_digest) == ISCSI_DATA_DIGEST_SIZE);
	if (icl_conn_receive_buf(request->ip_conn,
	    &received_digest, ISCSI_DATA_DIGEST_SIZE)) {
		ICL_DEBUG("failed to receive data digest");
		return (-1);
	}
	*availablep -= ISCSI_DATA_DIGEST_SIZE;

	/*
	 * Note that ip_data_mbuf also contains padding; since digest
	 * calculation is supposed to include that, we iterate over
	 * the entire ip_data_mbuf chain, not just ip_data_len bytes of it.
	 */
	valid_digest = icl_mbuf_to_crc32c(request->ip_data_mbuf);
	if (received_digest != valid_digest) {
		ICL_WARN("data digest check failed; got 0x%x, "
		    "should be 0x%x", received_digest, valid_digest);
		return (-1);
	}

	return (0);
}
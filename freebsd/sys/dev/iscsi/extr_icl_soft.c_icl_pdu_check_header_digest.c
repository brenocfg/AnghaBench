#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct icl_pdu {TYPE_1__* ip_bhs_mbuf; int /*<<< orphan*/ * ip_ahs_mbuf; TYPE_2__* ip_conn; } ;
typedef  int /*<<< orphan*/  received_digest ;
struct TYPE_4__ {int ic_header_crc32c; } ;
struct TYPE_3__ {int /*<<< orphan*/ * m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int /*<<< orphan*/  ICL_DEBUG (char*) ; 
 int /*<<< orphan*/  ICL_WARN (char*,scalar_t__,scalar_t__) ; 
 int ISCSI_HEADER_DIGEST_SIZE ; 
 scalar_t__ icl_conn_receive_buf (TYPE_2__*,scalar_t__*,int) ; 
 scalar_t__ icl_mbuf_to_crc32c (TYPE_1__*) ; 

__attribute__((used)) static int
icl_pdu_check_header_digest(struct icl_pdu *request, size_t *availablep)
{
	uint32_t received_digest, valid_digest;

	if (request->ip_conn->ic_header_crc32c == false)
		return (0);

	CTASSERT(sizeof(received_digest) == ISCSI_HEADER_DIGEST_SIZE);
	if (icl_conn_receive_buf(request->ip_conn,
	    &received_digest, ISCSI_HEADER_DIGEST_SIZE)) {
		ICL_DEBUG("failed to receive header digest");
		return (-1);
	}
	*availablep -= ISCSI_HEADER_DIGEST_SIZE;

	/* Temporary attach AHS to BHS to calculate header digest. */
	request->ip_bhs_mbuf->m_next = request->ip_ahs_mbuf;
	valid_digest = icl_mbuf_to_crc32c(request->ip_bhs_mbuf);
	request->ip_bhs_mbuf->m_next = NULL;
	if (received_digest != valid_digest) {
		ICL_WARN("header digest check failed; got 0x%x, "
		    "should be 0x%x", received_digest, valid_digest);
		return (-1);
	}

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct icl_pdu {scalar_t__ ip_data_len; TYPE_2__* ip_bhs_mbuf; TYPE_2__* ip_data_mbuf; struct icl_conn* ip_conn; } ;
struct icl_conn {scalar_t__ ic_data_crc32c; scalar_t__ ic_header_crc32c; } ;
typedef  int /*<<< orphan*/  digest ;
struct TYPE_6__ {size_t len; } ;
struct TYPE_7__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_WARN (char*) ; 
 scalar_t__ icl_mbuf_to_crc32c (TYPE_2__*) ; 
 size_t icl_pdu_padding (struct icl_pdu*) ; 
 int /*<<< orphan*/  icl_pdu_set_data_segment_length (struct icl_pdu*,scalar_t__) ; 
 size_t icl_pdu_size (struct icl_pdu*) ; 
 int m_append (TYPE_2__*,int,void*) ; 
 int /*<<< orphan*/  m_cat (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int
icl_pdu_finalize(struct icl_pdu *request)
{
	size_t padding, pdu_len;
	uint32_t digest, zero = 0;
	int ok;
	struct icl_conn *ic;

	ic = request->ip_conn;

	icl_pdu_set_data_segment_length(request, request->ip_data_len);

	pdu_len = icl_pdu_size(request);

	if (ic->ic_header_crc32c) {
		digest = icl_mbuf_to_crc32c(request->ip_bhs_mbuf);
		ok = m_append(request->ip_bhs_mbuf, sizeof(digest),
		    (void *)&digest);
		if (ok != 1) {
			ICL_WARN("failed to append header digest");
			return (1);
		}
	}

	if (request->ip_data_len != 0) {
		padding = icl_pdu_padding(request);
		if (padding > 0) {
			ok = m_append(request->ip_data_mbuf, padding,
			    (void *)&zero);
			if (ok != 1) {
				ICL_WARN("failed to append padding");
				return (1);
			}
		}

		if (ic->ic_data_crc32c) {
			digest = icl_mbuf_to_crc32c(request->ip_data_mbuf);

			ok = m_append(request->ip_data_mbuf, sizeof(digest),
			    (void *)&digest);
			if (ok != 1) {
				ICL_WARN("failed to append data digest");
				return (1);
			}
		}

		m_cat(request->ip_bhs_mbuf, request->ip_data_mbuf);
		request->ip_data_mbuf = NULL;
	}

	request->ip_bhs_mbuf->m_pkthdr.len = pdu_len;

	return (0);
}
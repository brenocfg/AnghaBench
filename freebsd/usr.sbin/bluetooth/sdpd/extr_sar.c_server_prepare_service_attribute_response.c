#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  size_t uint32_t ;
typedef  TYPE_2__* server_p ;
typedef  int /*<<< orphan*/  sdp_pdu_t ;
typedef  TYPE_3__* sdp_pdu_p ;
typedef  int /*<<< orphan*/  provider_t ;
typedef  size_t int32_t ;
struct TYPE_7__ {int len; } ;
struct TYPE_6__ {TYPE_1__* fdidx; int /*<<< orphan*/  const* req; } ;
struct TYPE_5__ {size_t rsp_cs; scalar_t__ rsp_size; int rsp_limit; int omtu; int /*<<< orphan*/  const* rsp; } ;

/* Variables and functions */
 int NG_L2CAP_MTU_MAXIMUM ; 
#define  SDP_DATA_SEQ16 130 
#define  SDP_DATA_SEQ32 129 
#define  SDP_DATA_SEQ8 128 
 size_t SDP_ERROR_CODE_INSUFFICIENT_RESOURCES ; 
 size_t SDP_ERROR_CODE_INVALID_CONTINUATION_STATE ; 
 size_t SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX ; 
 size_t SDP_ERROR_CODE_INVALID_SERVICE_RECORD_HANDLE ; 
 int /*<<< orphan*/  SDP_GET16 (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET32 (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET8 (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * provider_by_handle (size_t) ; 
 size_t server_prepare_attr_list (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int32_t
server_prepare_service_attribute_response(server_p srv, int32_t fd)
{
	uint8_t const	*req = srv->req + sizeof(sdp_pdu_t);
	uint8_t const	*req_end = req + ((sdp_pdu_p)(srv->req))->len;
	uint8_t		*rsp = srv->fdidx[fd].rsp;
	uint8_t const	*rsp_end = rsp + NG_L2CAP_MTU_MAXIMUM;

	uint8_t		*ptr = NULL;
	provider_t	*provider = NULL;
	uint32_t	 handle;
	int32_t		 type, rsp_limit, aidlen, cslen, cs;

	/*
	 * Minimal Service Attribute Request request
	 *
	 * value32		- 4 bytes ServiceRecordHandle
	 * value16		- 2 bytes MaximumAttributeByteCount
	 * seq8 len8		- 2 bytes
	 *	uint16 value16	- 3 bytes AttributeIDList
	 * value8		- 1 byte  ContinuationState
	 */

	if (req_end - req < 12)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Get ServiceRecordHandle and MaximumAttributeByteCount */
	SDP_GET32(handle, req);
	SDP_GET16(rsp_limit, req);
	if (rsp_limit <= 0)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Get size of AttributeIDList */
	aidlen = 0;
	SDP_GET8(type, req);
	switch (type) {
	case SDP_DATA_SEQ8:
		SDP_GET8(aidlen, req);
		break;

	case SDP_DATA_SEQ16:
		SDP_GET16(aidlen, req);
		break;

	case SDP_DATA_SEQ32:
		SDP_GET32(aidlen, req);
 		break;
	}
	if (aidlen <= 0)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	ptr = (uint8_t *) req + aidlen;

	/* Get ContinuationState */
	if (ptr + 1 > req_end)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);
		
	SDP_GET8(cslen, ptr);
	if (cslen != 0) {
		if (cslen != 2 || req_end - ptr != 2)
			return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

		SDP_GET16(cs, ptr);
	} else
		cs = 0;

	/* Process the request. First, check continuation state */
	if (srv->fdidx[fd].rsp_cs != cs)
		return (SDP_ERROR_CODE_INVALID_CONTINUATION_STATE);
	if (srv->fdidx[fd].rsp_size > 0)
		return (0);

	/* Lookup record handle */
	if ((provider = provider_by_handle(handle)) == NULL)
		return (SDP_ERROR_CODE_INVALID_SERVICE_RECORD_HANDLE);

	/*
	 * Service Attribute Response format
	 *
	 * value16		- 2 bytes  AttributeListByteCount (not incl.)
	 * seq8 len16		- 3 bytes
	 *	attr value	- 3+ bytes AttributeList
	 *	[ attr value ]
	 */

	cs = server_prepare_attr_list(provider, req, req+aidlen, rsp, rsp_end);
	if (cs < 0)
		return (SDP_ERROR_CODE_INSUFFICIENT_RESOURCES);

	/* Set reply size (not counting PDU header and continuation state) */
	srv->fdidx[fd].rsp_limit = srv->fdidx[fd].omtu - sizeof(sdp_pdu_t) - 2;
	if (srv->fdidx[fd].rsp_limit > rsp_limit)
		srv->fdidx[fd].rsp_limit = rsp_limit;

	srv->fdidx[fd].rsp_size = cs;
	srv->fdidx[fd].rsp_cs = 0;

	return (0);
}
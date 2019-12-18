#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_3__* server_p ;
typedef  int /*<<< orphan*/  sdp_pdu_t ;
typedef  TYPE_4__* sdp_pdu_p ;
struct TYPE_13__ {size_t fd; TYPE_1__* profile; } ;
typedef  TYPE_5__ provider_t ;
typedef  size_t int32_t ;
struct TYPE_12__ {int len; } ;
struct TYPE_11__ {TYPE_2__* fdidx; int /*<<< orphan*/ * req; } ;
struct TYPE_10__ {int rsp_size; scalar_t__ rsp_cs; int /*<<< orphan*/ * rsp; scalar_t__ omtu; scalar_t__ rsp_limit; int /*<<< orphan*/  priv; int /*<<< orphan*/  control; } ;
struct TYPE_9__ {int dsize; scalar_t__ (* valid ) (int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 size_t SDP_ERROR_CODE_INSUFFICIENT_RESOURCES ; 
 size_t SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX ; 
 size_t SDP_ERROR_CODE_INVALID_SERVICE_RECORD_HANDLE ; 
 int /*<<< orphan*/  SDP_GET32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* provider_by_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ provider_update (TYPE_5__*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/  const*,int) ; 

int32_t
server_prepare_service_change_response(server_p srv, int32_t fd)
{
	uint8_t const	*req = srv->req + sizeof(sdp_pdu_t);
	uint8_t const	*req_end = req + ((sdp_pdu_p)(srv->req))->len;
	uint8_t		*rsp = srv->fdidx[fd].rsp;

	provider_t	*provider = NULL;
	uint32_t	 handle;

	/*
	 * Minimal Service Change Request
	 *
	 * value32	- handle 4 bytes
	 */

	if (!srv->fdidx[fd].control ||
	    !srv->fdidx[fd].priv || req_end - req < 4)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Get handle */
	SDP_GET32(handle, req);

	/* Lookup provider */
	provider = provider_by_handle(handle);
	if (provider == NULL || provider->fd != fd)
		return (SDP_ERROR_CODE_INVALID_SERVICE_RECORD_HANDLE);

	/* Validate user data */
	if (req_end - req < provider->profile->dsize ||
	    provider->profile->valid == NULL ||
	    (provider->profile->valid)(req, req_end - req) == 0)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Update provider */
	if (provider_update(provider, req, req_end - req) < 0)
		return (SDP_ERROR_CODE_INSUFFICIENT_RESOURCES);

	SDP_PUT16(0, rsp);
	
	/* Set reply size */
	srv->fdidx[fd].rsp_limit = srv->fdidx[fd].omtu - sizeof(sdp_pdu_t);
	srv->fdidx[fd].rsp_size = rsp - srv->fdidx[fd].rsp;
	srv->fdidx[fd].rsp_cs = 0;

	return (0);
}
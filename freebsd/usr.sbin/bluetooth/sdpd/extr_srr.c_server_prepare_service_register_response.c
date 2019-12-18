#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_2__* server_p ;
typedef  int /*<<< orphan*/  sdp_pdu_t ;
typedef  TYPE_3__* sdp_pdu_p ;
struct TYPE_13__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_4__ provider_t ;
struct TYPE_14__ {int dsize; scalar_t__ (* valid ) (int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_5__ profile_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/ * bdaddr_p ;
struct TYPE_12__ {int len; } ;
struct TYPE_11__ {TYPE_1__* fdidx; int /*<<< orphan*/ * req; } ;
struct TYPE_10__ {int rsp_size; scalar_t__ rsp_cs; int /*<<< orphan*/ * rsp; scalar_t__ omtu; scalar_t__ rsp_limit; int /*<<< orphan*/  priv; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 size_t SDP_ERROR_CODE_INSUFFICIENT_RESOURCES ; 
 size_t SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX ; 
 int /*<<< orphan*/  SDP_GET16 (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDP_PUT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* profile_get_descriptor (size_t) ; 
 TYPE_4__* provider_register (TYPE_5__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/  const*,int) ; 

int32_t
server_prepare_service_register_response(server_p srv, int32_t fd)
{
	uint8_t const	*req = srv->req + sizeof(sdp_pdu_t);
	uint8_t const	*req_end = req + ((sdp_pdu_p)(srv->req))->len;
	uint8_t		*rsp = srv->fdidx[fd].rsp;

	profile_t	*profile = NULL;
	provider_t	*provider = NULL;
	bdaddr_t	*bdaddr = NULL;
	int32_t		 uuid;

	/*
	 * Minimal Service Register Request
	 *
	 * value16	- uuid 2 bytes
	 * bdaddr	- BD_ADDR 6 bytes
	 */

	if (!srv->fdidx[fd].control ||
	    !srv->fdidx[fd].priv || req_end - req < 8)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Get ServiceClass UUID */
	SDP_GET16(uuid, req);

	/* Get BD_ADDR */
	bdaddr = (bdaddr_p) req;
	req += sizeof(*bdaddr);

	/* Lookup profile descriptror */
	profile = profile_get_descriptor(uuid);
	if (profile == NULL)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Validate user data */
	if (req_end - req < profile->dsize ||
	    profile->valid == NULL ||
	    (profile->valid)(req, req_end - req) == 0)
		return (SDP_ERROR_CODE_INVALID_REQUEST_SYNTAX);

	/* Register provider */
	provider = provider_register(profile, bdaddr, fd, req, req_end - req);
	if (provider == NULL)
		return (SDP_ERROR_CODE_INSUFFICIENT_RESOURCES);

	SDP_PUT16(0, rsp);
	SDP_PUT32(provider->handle, rsp);
	
	/* Set reply size */
	srv->fdidx[fd].rsp_limit = srv->fdidx[fd].omtu - sizeof(sdp_pdu_t);
	srv->fdidx[fd].rsp_size = rsp - srv->fdidx[fd].rsp;
	srv->fdidx[fd].rsp_cs = 0;

	return (0);
}
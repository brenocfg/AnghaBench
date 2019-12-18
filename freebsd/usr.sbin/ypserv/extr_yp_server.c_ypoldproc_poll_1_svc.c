#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* peer; scalar_t__ ordernum; int /*<<< orphan*/  map; int /*<<< orphan*/  domain; } ;
struct TYPE_16__ {TYPE_2__ yp_resp_map_parmstype; } ;
struct TYPE_17__ {TYPE_3__ ypresponse_u; int /*<<< orphan*/  yp_resptype; } ;
typedef  TYPE_4__ ypresponse ;
struct TYPE_18__ {scalar_t__ stat; scalar_t__ ordernum; } ;
typedef  TYPE_5__ ypresp_order ;
struct TYPE_19__ {scalar_t__ stat; char* peer; } ;
typedef  TYPE_6__ ypresp_master ;
struct TYPE_21__ {int /*<<< orphan*/  map; int /*<<< orphan*/  domain; } ;
struct TYPE_14__ {TYPE_9__ yp_req_nokeytype; } ;
struct TYPE_20__ {scalar_t__ yp_reqtype; TYPE_1__ yprequest_u; } ;
typedef  TYPE_7__ yprequest ;
struct svc_req {int dummy; } ;

/* Variables and functions */
 scalar_t__ YPREQ_MAP_PARMS ; 
 int /*<<< orphan*/  YPRESP_MAP_PARMS ; 
 scalar_t__ YP_TRUE ; 
 TYPE_6__* ypproc_master_2_svc (TYPE_9__*,struct svc_req*) ; 
 TYPE_5__* ypproc_order_2_svc (TYPE_9__*,struct svc_req*) ; 

ypresponse *
ypoldproc_poll_1_svc(yprequest *argp, struct svc_req *rqstp)
{
	static ypresponse  result;
	ypresp_master *v2_result1;
	ypresp_order *v2_result2;

	result.yp_resptype = YPRESP_MAP_PARMS;
	result.ypresponse_u.yp_resp_map_parmstype.domain =
		argp->yprequest_u.yp_req_nokeytype.domain;
	result.ypresponse_u.yp_resp_map_parmstype.map =
		argp->yprequest_u.yp_req_nokeytype.map;
	/*
	 * Hmm... there is no 'status' value in the
	 * yp_resp_map_parmstype structure, so I have to
	 * guess at what to do to indicate a failure.
	 * I hope this is right.
	 */
	result.ypresponse_u.yp_resp_map_parmstype.ordernum = 0;
	result.ypresponse_u.yp_resp_map_parmstype.peer = "";

	if (argp->yp_reqtype != YPREQ_MAP_PARMS) {
		return(&result);
	}

	v2_result1 = ypproc_master_2_svc(&argp->yprequest_u.yp_req_nokeytype,
									rqstp);
	if (v2_result1 == NULL)
		return(NULL);

	if (v2_result1->stat != YP_TRUE) {
		return(&result);
	}

	v2_result2 = ypproc_order_2_svc(&argp->yprequest_u.yp_req_nokeytype,
									rqstp);
	if (v2_result2 == NULL)
		return(NULL);

	if (v2_result2->stat != YP_TRUE) {
		return(&result);
	}

	result.ypresponse_u.yp_resp_map_parmstype.peer =
		v2_result1->peer;
	result.ypresponse_u.yp_resp_map_parmstype.ordernum =
		v2_result2->ordernum;

	return (&result);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* keydat_val; scalar_t__ keydat_len; } ;
struct TYPE_10__ {char* valdat_val; scalar_t__ valdat_len; } ;
struct TYPE_16__ {int /*<<< orphan*/  stat; TYPE_2__ key; TYPE_1__ val; } ;
struct TYPE_13__ {TYPE_9__ yp_resp_key_valtype; } ;
struct TYPE_14__ {TYPE_4__ ypresponse_u; int /*<<< orphan*/  yp_resptype; } ;
typedef  TYPE_5__ ypresponse ;
typedef  int /*<<< orphan*/  ypresp_key_val ;
struct TYPE_12__ {int /*<<< orphan*/  yp_req_nokeytype; } ;
struct TYPE_15__ {scalar_t__ yp_reqtype; TYPE_3__ yprequest_u; } ;
typedef  TYPE_6__ yprequest ;
struct svc_req {int dummy; } ;

/* Variables and functions */
 scalar_t__ YPREQ_NOKEY ; 
 int /*<<< orphan*/  YPRESP_KEY_VAL ; 
 int /*<<< orphan*/  YP_BADARGS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_9__*,int) ; 
 int /*<<< orphan*/ * ypproc_first_2_svc (int /*<<< orphan*/ *,struct svc_req*) ; 

ypresponse *
ypoldproc_first_1_svc(yprequest *argp, struct svc_req *rqstp)
{
	static ypresponse  result;
	ypresp_key_val *v2_result;

	result.yp_resptype = YPRESP_KEY_VAL;
	result.ypresponse_u.yp_resp_key_valtype.val.valdat_val =
	result.ypresponse_u.yp_resp_key_valtype.key.keydat_val = "";
	result.ypresponse_u.yp_resp_key_valtype.val.valdat_len =
	result.ypresponse_u.yp_resp_key_valtype.key.keydat_len = 0;

	if (argp->yp_reqtype != YPREQ_NOKEY) {
		result.ypresponse_u.yp_resp_key_valtype.stat = YP_BADARGS;
		return(&result);
	}

	v2_result = ypproc_first_2_svc(&argp->yprequest_u.yp_req_nokeytype,
									rqstp);
	if (v2_result == NULL)
		return(NULL);

	bcopy(v2_result, &result.ypresponse_u.yp_resp_key_valtype,
	      sizeof(ypresp_key_val));

	return (&result);
}
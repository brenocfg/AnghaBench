#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ses_requests; } ;
typedef  TYPE_1__ ses_softc_t ;
struct TYPE_11__ {int result; int /*<<< orphan*/  elm_stat; int /*<<< orphan*/  elm_idx; } ;
typedef  TYPE_2__ ses_control_request_t ;
struct TYPE_12__ {int* cstat; int /*<<< orphan*/  elm_idx; } ;
typedef  TYPE_3__ encioc_elm_status_t ;
struct TYPE_13__ {int /*<<< orphan*/  periph; TYPE_1__* enc_private; } ;
typedef  TYPE_4__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PUSER ; 
 int SESCTL_CSEL ; 
 int /*<<< orphan*/  SES_PROCESS_CONTROL_REQS ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_sleep (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enc_update_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int
ses_set_elm_status(enc_softc_t *enc, encioc_elm_status_t *elms, int slpflag)
{
	ses_control_request_t req;
	ses_softc_t	     *ses;

	/* If this is clear, we don't do diddly.  */
	if ((elms->cstat[0] & SESCTL_CSEL) == 0)
		return (0);

	ses = enc->enc_private;
	req.elm_idx = elms->elm_idx;
	memcpy(&req.elm_stat, elms->cstat, sizeof(req.elm_stat));

	TAILQ_INSERT_TAIL(&ses->ses_requests, &req, links);
	enc_update_request(enc, SES_PROCESS_CONTROL_REQS);
	cam_periph_sleep(enc->periph, &req, PUSER, "encstat", 0);

	return (req.result);
}
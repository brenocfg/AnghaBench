#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  ses_requests; } ;
typedef  TYPE_2__ ses_softc_t ;
struct TYPE_9__ {int comstatus; } ;
struct TYPE_11__ {int result; TYPE_1__ elm_stat; int /*<<< orphan*/  elm_idx; } ;
typedef  TYPE_3__ ses_control_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  periph; TYPE_2__* enc_private; } ;
typedef  TYPE_4__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  SES_PROCESS_CONTROL_REQS ; 
 int /*<<< orphan*/  SES_SETSTATUS_ENC_IDX ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_sleep (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enc_update_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 

__attribute__((used)) static int
ses_set_enc_status(enc_softc_t *enc, uint8_t encstat, int slpflag)
{
	ses_control_request_t req;
	ses_softc_t	     *ses;

	ses = enc->enc_private;
	req.elm_idx = SES_SETSTATUS_ENC_IDX;
	req.elm_stat.comstatus = encstat & 0xf;
	
	TAILQ_INSERT_TAIL(&ses->ses_requests, &req, links);
	enc_update_request(enc, SES_PROCESS_CONTROL_REQS);
	cam_periph_sleep(enc->periph, &req, PUSER, "encstat", 0);

	return (req.result);
}
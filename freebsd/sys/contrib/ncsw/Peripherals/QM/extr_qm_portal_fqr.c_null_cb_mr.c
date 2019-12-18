#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_LowQmPortal; } ;
typedef  TYPE_4__ t_QmPortal ;
typedef  struct qman_fq* t_Handle ;
struct qman_fq {int dummy; } ;
struct TYPE_7__ {int portal; } ;
struct qm_mr_entry {int verb; TYPE_3__ dcern; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_6__ {TYPE_1__ config; } ;

/* Variables and functions */
 int QM_MR_VERB_DC_ERN ; 
 int /*<<< orphan*/  UNUSED (struct qman_fq*) ; 
 int /*<<< orphan*/  XX_Print (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void null_cb_mr(t_Handle                   h_App,
                       t_Handle                   h_QmPortal,
                       struct qman_fq             *p_Fq,
                       const struct qm_mr_entry   *p_Msg)
{
    t_QmPortal      *p_QmPortal = (t_QmPortal *)h_QmPortal;

    UNUSED(p_Fq);UNUSED(h_App);

    if ((p_Msg->verb & QM_MR_VERB_DC_ERN) == QM_MR_VERB_DC_ERN)
        XX_Print("Ignoring unowned MR frame on cpu %d, dc-portal 0x%02x.\n",
                 p_QmPortal->p_LowQmPortal->config.cpu,p_Msg->dcern.portal);
    else
        XX_Print("Ignoring unowned MR frame on cpu %d, verb 0x%02x.\n",
                 p_QmPortal->p_LowQmPortal->config.cpu,p_Msg->verb);
}
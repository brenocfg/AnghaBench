#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int icr; int tbe; int frtt; int rif; int rdf; int nrm; int trm; int cdf; int adtf; scalar_t__ mcr; int /*<<< orphan*/  pcr; int /*<<< orphan*/  class_type; } ;
typedef  TYPE_1__ srv_cls_param_t ;
struct TYPE_6__ {int /*<<< orphan*/  LineRate; } ;
typedef  TYPE_2__ IADEV ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ABR ; 

__attribute__((used)) static void init_abr_vc (IADEV *dev, srv_cls_param_t *srv_p) {
  srv_p->class_type = ATM_ABR;
  srv_p->pcr        = dev->LineRate;
  srv_p->mcr        = 0;
  srv_p->icr        = 0x055cb7;
  srv_p->tbe        = 0xffffff;
  srv_p->frtt       = 0x3a;
  srv_p->rif        = 0xf;
  srv_p->rdf        = 0xb;
  srv_p->nrm        = 0x4;
  srv_p->trm        = 0x7;
  srv_p->cdf        = 0x3;
  srv_p->adtf       = 50;
}
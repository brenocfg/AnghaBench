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
struct TYPE_6__ {int (* cb_2 ) (int,int,TYPE_2__*) ;} ;
struct TYPE_7__ {int ver; TYPE_1__ cb; void* arg; } ;
typedef  TYPE_2__ BN_GENCB ;

/* Variables and functions */

void BN_GENCB_set(BN_GENCB *gencb, int (*callback) (int, int, BN_GENCB *),
                  void *cb_arg)
{
    BN_GENCB *tmp_gencb = gencb;
    tmp_gencb->ver = 2;
    tmp_gencb->arg = cb_arg;
    tmp_gencb->cb.cb_2 = callback;
}
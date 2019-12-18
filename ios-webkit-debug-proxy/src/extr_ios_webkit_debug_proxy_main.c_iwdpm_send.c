#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sm_t ;
typedef  TYPE_2__* iwdpm_t ;
typedef  TYPE_3__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_7__ {TYPE_1__* sm; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* send ) (TYPE_1__*,int,char const*,size_t,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,char const*,size_t,int /*<<< orphan*/ *) ; 

iwdp_status iwdpm_send(iwdp_t iwdp, int fd, const char *data, size_t length) {
  sm_t sm = ((iwdpm_t)iwdp->state)->sm;
  return sm->send(sm, fd, data, length, NULL);
}
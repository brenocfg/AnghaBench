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
typedef  int /*<<< orphan*/  sm_status ;
typedef  TYPE_2__* iwdpm_t ;
typedef  TYPE_3__* iwdp_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* on_accept ) (TYPE_3__*,int,void*,int,void**) ;} ;
struct TYPE_7__ {TYPE_3__* iwdp; } ;
struct TYPE_6__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,void*,int,void**) ; 

sm_status iwdpm_on_accept(sm_t sm, int s_fd, void *s_value,
    int fd, void **to_value) {
  iwdp_t iwdp = ((iwdpm_t)sm->state)->iwdp;
  return iwdp->on_accept(iwdp, s_fd, s_value, fd, to_value);
}
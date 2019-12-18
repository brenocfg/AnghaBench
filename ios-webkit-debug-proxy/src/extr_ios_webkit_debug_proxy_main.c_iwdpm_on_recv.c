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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  TYPE_1__* sm_t ;
typedef  int /*<<< orphan*/  sm_status ;
typedef  TYPE_2__* iwdpm_t ;
typedef  TYPE_3__* iwdp_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* on_recv ) (TYPE_3__*,int,void*,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_3__* iwdp; } ;
struct TYPE_6__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,void*,char const*,int /*<<< orphan*/ ) ; 

sm_status iwdpm_on_recv(sm_t sm, int fd, void *value,
    const char *buf, ssize_t length) {
  iwdp_t iwdp = ((iwdpm_t)sm->state)->iwdp;
  return iwdp->on_recv(iwdp, fd, value, buf, length);
}
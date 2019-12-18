#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {TYPE_1__* xp_socket; int /*<<< orphan*/  xp_snt_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_snd; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atomic_load_acq_32 (int /*<<< orphan*/ *) ; 
 scalar_t__ sbused (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
svc_vc_ack(SVCXPRT *xprt, uint32_t *ack)
{

	*ack = atomic_load_acq_32(&xprt->xp_snt_cnt);
	*ack -= sbused(&xprt->xp_socket->so_snd);
	return (TRUE);
}
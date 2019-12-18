#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ifp; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla_hw_tx_done (TYPE_1__*) ; 
 int /*<<< orphan*/  qla_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla_tx_done(void *context, int pending)
{
	qla_host_t *ha = context;

	qla_hw_tx_done(ha);
	qla_start(ha->ifp);
}
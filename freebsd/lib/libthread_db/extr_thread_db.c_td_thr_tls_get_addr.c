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
struct TYPE_7__ {TYPE_3__* th_ta; } ;
typedef  TYPE_2__ td_thrhandle_t ;
struct TYPE_8__ {TYPE_1__* ta_ops; } ;
typedef  TYPE_3__ td_thragent_t ;
typedef  int /*<<< orphan*/  td_err_e ;
typedef  int /*<<< orphan*/  psaddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* to_thr_tls_get_addr ) (TYPE_2__ const*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

td_err_e
td_thr_tls_get_addr(const td_thrhandle_t *th, psaddr_t linkmap, size_t offset,
    psaddr_t *address)
{
	const td_thragent_t *ta = th->th_ta;
	return (ta->ta_ops->to_thr_tls_get_addr(th, linkmap, offset, address));
}
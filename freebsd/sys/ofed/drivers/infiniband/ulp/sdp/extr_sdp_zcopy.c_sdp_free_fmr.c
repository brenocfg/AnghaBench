#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct ib_umem {int dummy; } ;
struct ib_pool_fmr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_fmr_pool_unmap (struct ib_pool_fmr*) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 TYPE_1__* sdp_sk (struct socket*) ; 

void sdp_free_fmr(struct socket *sk, struct ib_pool_fmr **_fmr, struct ib_umem **_umem)
{
	if (!sdp_sk(sk)->qp_active)
		return;

	ib_fmr_pool_unmap(*_fmr);
	*_fmr = NULL;

	ib_umem_release(*_umem);
	*_umem = NULL;
}
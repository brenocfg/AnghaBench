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
struct umtx_shm_reg {int /*<<< orphan*/  ushm_obj; TYPE_1__* ushm_cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_ruidinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  chgumtxcnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (TYPE_1__*) ; 
 int /*<<< orphan*/  shm_drop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct umtx_shm_reg*) ; 
 int /*<<< orphan*/  umtx_shm_reg_zone ; 

__attribute__((used)) static void
umtx_shm_free_reg(struct umtx_shm_reg *reg)
{

	chgumtxcnt(reg->ushm_cred->cr_ruidinfo, -1, 0);
	crfree(reg->ushm_cred);
	shm_drop(reg->ushm_obj);
	uma_zfree(umtx_shm_reg_zone, reg);
}
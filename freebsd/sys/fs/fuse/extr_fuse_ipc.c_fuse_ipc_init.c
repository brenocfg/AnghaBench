#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fuse_ticket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  counter_u64_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fticket_ctor ; 
 int /*<<< orphan*/  fticket_dtor ; 
 int /*<<< orphan*/  fticket_fini ; 
 int /*<<< orphan*/  fticket_init ; 
 int /*<<< orphan*/  fuse_ticket_count ; 
 int /*<<< orphan*/  ticket_zone ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fuse_ipc_init(void)
{
	ticket_zone = uma_zcreate("fuse_ticket", sizeof(struct fuse_ticket),
	    fticket_ctor, fticket_dtor, fticket_init, fticket_fini,
	    UMA_ALIGN_PTR, 0);
	fuse_ticket_count = counter_u64_alloc(M_WAITOK);
}
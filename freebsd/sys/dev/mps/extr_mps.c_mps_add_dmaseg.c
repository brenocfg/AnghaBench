#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  size_t u_int ;
struct mps_command {int dummy; } ;
typedef  int /*<<< orphan*/  sge ;
struct TYPE_4__ {int /*<<< orphan*/  Address; int /*<<< orphan*/  FlagsLength; } ;
typedef  TYPE_1__ MPI2_SGE_SIMPLE64 ;

/* Variables and functions */
 size_t MPI2_SGE_FLAGS_64_BIT_ADDRESSING ; 
 size_t MPI2_SGE_FLAGS_SHIFT ; 
 size_t MPI2_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  htole32 (size_t) ; 
 int /*<<< orphan*/  mps_from_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mps_push_sge (struct mps_command*,TYPE_1__*,int,int) ; 

int
mps_add_dmaseg(struct mps_command *cm, vm_paddr_t pa, size_t len, u_int flags,
    int segsleft)
{
	MPI2_SGE_SIMPLE64 sge;

	/*
	 * This driver always uses 64-bit address elements for simplicity.
	 */
	bzero(&sge, sizeof(sge));
	flags |= MPI2_SGE_FLAGS_SIMPLE_ELEMENT |
	    MPI2_SGE_FLAGS_64_BIT_ADDRESSING;
	sge.FlagsLength = htole32(len | (flags << MPI2_SGE_FLAGS_SHIFT));
	mps_from_u64(pa, &sge.Address);

	return (mps_push_sge(cm, &sge, sizeof sge, segsleft));
}
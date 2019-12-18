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
typedef  size_t u_int ;
struct sec_softc {int dummy; } ;
struct sec_hw_desc_ptr {int /*<<< orphan*/  shdp_ptr; scalar_t__ shdp_j; scalar_t__ shdp_extent; int /*<<< orphan*/  shdp_length; } ;
struct sec_desc {TYPE_1__* sd_desc; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_2__ {struct sec_hw_desc_ptr* shd_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_LOCK_ASSERT (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  descriptors ; 

__attribute__((used)) static int
sec_make_pointer_direct(struct sec_softc *sc, struct sec_desc *desc, u_int n,
    bus_addr_t data, bus_size_t dsize)
{
	struct sec_hw_desc_ptr *ptr;

	SEC_LOCK_ASSERT(sc, descriptors);

	ptr = &(desc->sd_desc->shd_pointer[n]);
	ptr->shdp_length = dsize;
	ptr->shdp_extent = 0;
	ptr->shdp_j = 0;
	ptr->shdp_ptr = data;

	return (0);
}
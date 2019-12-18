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
struct vmxnet3_softc {int dummy; } ;

/* Variables and functions */
 int vmxnet3_alloc_mcast_table (struct vmxnet3_softc*) ; 
 int vmxnet3_alloc_shared_data (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_init_shared_data (struct vmxnet3_softc*) ; 

__attribute__((used)) static int
vmxnet3_alloc_data(struct vmxnet3_softc *sc)
{
	int error;

	error = vmxnet3_alloc_shared_data(sc);
	if (error)
		return (error);

	error = vmxnet3_alloc_mcast_table(sc);
	if (error)
		return (error);

	vmxnet3_init_shared_data(sc);

	return (0);
}